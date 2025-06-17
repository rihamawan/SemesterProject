//#include <iostream>
//#include "GameEngine.h"
//#include "LevelManager.h"
//#include "Projectile.h"
//#include "MyString.h"
//
//int main() {
//    GameEngine engine("level1.txt","savedFile.bin","logger.txt");
//    Logger logger("log.txt");
//    LevelManager levelManager(logger);
//
//    // Initialize players
//    Player p1(MyString("Player 1"), XYCoord(50, 550));
//    Player p2(MyString("Player 2"), XYCoord(750, 550));
//    engine.addPlayer(p1);
//    engine.addPlayer(p2);
//
//    int currentLevel = 1;
//    const int maxLevels = 5;
//
//    while (currentLevel <= maxLevels) {
//        Level level;
//        try {
//            levelManager.loadLevel(currentLevel, level);
//        }
//        catch (const std::exception& e) {
//            std::cerr << "Error loading level: " << e.what() << "\n";
//            break;
//        }
//
//        std::cout << "Level " << currentLevel << " Start!\n";
//        bool levelComplete = false;
//
//        int playerTurn = 0;
//
//        while (!levelComplete) {
//            Player& currentPlayer = engine.getPlayer(playerTurn);
//            std::cout << currentPlayer.getName().returnArray() << "'s turn!\n";
//
//            float angle, power;
//            std::cout << "Enter angle: ";
//            std::cin >> angle;
//            std::cout << "Enter power: ";
//            std::cin >> power;
//
//            Projectile projectile(currentPlayer.getPosition(), XYCoord(0, 0));
//            projectile.launch(currentPlayer.getPosition(), angle, power, level.getWind());
//            currentPlayer.incrementTries();
//
//            while (!projectile.isOffScreen(800, 600)) {
//                projectile.update(0.1f, level.getWind());
//
//                for (int i = 0; i < level.getTargetCount(); ++i) {
//                    Target* target = level.getTarget(i);
//                    if (!target->isDestroyed() && target->checkHit(projectile.getPosition(),projectile.getRadius())) {
//                        std::cout << "Hit target " << i + 1 << "!\n";
//                        target->setDestroyed(true);
//                        currentPlayer.addScore(10);
//                        projectile.reset(); // stop further movement
//                        break;
//                    }
//                }
//
//                if (!projectile.isActive()) break;
//            }
//
//            // Check if all targets destroyed
//            levelComplete = true;
//            for (int i = 0; i < level.getTargetCount(); ++i) {
//                if (!level.getTarget(i)->isDestroyed()) {
//                    levelComplete = false;
//                    break;
//                }
//            }
//
//            playerTurn = (playerTurn + 1) % 2;
//        }
//
//        std::cout << "Level " << currentLevel << " complete!\n";
//        if (p1.getTries() < p2.getTries()) {
//            std::cout << p1.getName() << " wins this level!\n";
//        }
//        else if (p2.getTries() < p1.getTries()) {
//            std::cout << p2.getName() << " wins this level!\n";
//        }
//        else {
//            std::cout << "It's a tie on this level!\n";
//        }
//        p1.resetTries();
//        p2.resetTries();
//
//        currentLevel++;
//    }
//
//    // Final scores
//    std::cout << "Final Scores:\n";
//    for (int i = 0; i < engine.getPlayerCount(); ++i) {
//        const Player& p = engine.getPlayer(i);
//        std::cout << p.getName().returnArray() << ": " << p.getScore() << "\n";
//    }
//
//    return 0;
//}


#include "raylib.h"
#include <cmath>
#include "XYCoord.h"
#include "Level.h"
#include "LevelManager.h"
#include "Logger.h"

float Clamp(float value, float min, float max) {
    return (value < min) ? min : (value > max) ? max : value;
}

void DrawHUD(int playerTurn, float angle, float power, int level, XYCoord wind) {
    DrawText(TextFormat("Player Turn: %d", playerTurn + 1), 20, 20, 20, BLACK);
    DrawText(TextFormat("Angle: %.1f°", angle), 20, 50, 20, DARKBLUE);
    DrawText(TextFormat("Power: %.0f", power), 20, 80, 20, DARKGREEN);
    DrawText(TextFormat("Level: %d", level), 20, 110, 20, MAROON);
    DrawText(TextFormat("Wind: [%.1f, %.1f]", wind.x, wind.y), 20, 140, 20, PURPLE);
}

void DrawProjectilePath(XYCoord start, XYCoord velocity, XYCoord wind, float gravity) {
    float dt = 0.1f;
    XYCoord pos = start;
    XYCoord vel = velocity;

    for (int i = 0; i < 200; ++i) {
        DrawCircle((int)pos.x, (int)pos.y, 2, RED);
        vel.x += wind.x * dt;
        vel.y += (gravity + wind.y) * dt;
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        if (pos.y > GetScreenHeight()) break;
    }
}

int main() {
    InitWindow(1000, 600, "Projectile Simulator");
    SetTargetFPS(60);

    Logger logger("log.txt");
    LevelManager levelManager(logger);
    Level currentLevel;
    levelManager.loadLevel(1, currentLevel);

    int playerTurn = 0;
    float angle = 45.0f;
    float power = 200.0f;
    int level = 1;
    XYCoord wind = currentLevel.getWind();
    float gravity = 9.8f;

    XYCoord projPos = XYCoord(100, 500);
    XYCoord projVel;
    bool projectileFired = false;

    while (!WindowShouldClose()) {
        XYCoord base = (playerTurn == 0) ? XYCoord(100, 500) : XYCoord(900, 500);

        // Input
        if (IsKeyDown(KEY_LEFT)) angle -= 60 * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) angle += 60 * GetFrameTime();
        if (IsKeyDown(KEY_UP)) power += 200 * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) power -= 200 * GetFrameTime();

        angle = Clamp(angle, -90.0f, 90.0f);
        power = Clamp(power, 50.0f, 1000.0f);

        // Fire
        if (IsKeyPressed(KEY_SPACE) && !projectileFired) {
            float rad = angle * (3.14159f / 180.0f);
            float speed = power / 10.0f;
            projVel = XYCoord(cosf(rad) * speed, -sinf(rad) * speed);
            projPos = base;
            projectileFired = true;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        currentLevel.draw();
        DrawHUD(playerTurn, angle, power, level, wind);

        if (projectileFired) {
            projVel.x += wind.x * GetFrameTime();
            projVel.y += gravity * GetFrameTime();
            projPos.x += projVel.x * GetFrameTime();
            projPos.y += projVel.y * GetFrameTime();

            DrawCircle((int)projPos.x, (int)projPos.y, 5, ORANGE);

            if (projPos.y > GetScreenHeight()) {
                projectileFired = false;
                playerTurn = (playerTurn + 1) % 2;
            }
        }
        else {
            float rad = angle * (3.14159f / 180.0f);
            float speed = power / 10.0f;
            XYCoord initVel(cosf(rad) * speed, -sinf(rad) * speed);
            DrawProjectilePath(base, initVel, wind, gravity);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

