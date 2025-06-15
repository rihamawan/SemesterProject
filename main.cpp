#include <iostream>
#include "GameEngine.h"
#include "LevelManager.h"
#include "Projectile.h"
#include "MyString.h"

int main() {
    GameEngine engine("level1.txt","savedFile.bin","logger.txt");
    Logger logger("log.txt");
    LevelManager levelManager(logger);

    // Initialize players
    Player p1(MyString("Player 1"), XYCoord(50, 550));
    Player p2(MyString("Player 2"), XYCoord(750, 550));
    engine.addPlayer(p1);
    engine.addPlayer(p2);

    int currentLevel = 1;
    const int maxLevels = 5;

    while (currentLevel <= maxLevels) {
        Level level;
        try {
            levelManager.loadLevel(currentLevel, level);
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading level: " << e.what() << "\n";
            break;
        }

        std::cout << "Level " << currentLevel << " Start!\n";
        bool levelComplete = false;

        int playerTurn = 0;

        while (!levelComplete) {
            Player& currentPlayer = engine.getPlayer(playerTurn);
            std::cout << currentPlayer.getName().returnArray() << "'s turn!\n";

            float angle, power;
            std::cout << "Enter angle: ";
            std::cin >> angle;
            std::cout << "Enter power: ";
            std::cin >> power;

            Projectile projectile(currentPlayer.getPosition(), XYCoord(0, 0));
            projectile.launch(currentPlayer.getPosition(), angle, power, level.getWind());
            currentPlayer.incrementTries();

            while (!projectile.isOffScreen(800, 600)) {
                projectile.update(0.1f, level.getWind());

                for (int i = 0; i < level.getTargetCount(); ++i) {
                    Target* target = level.getTarget(i);
                    if (!target->isDestroyed() && target->checkHit(projectile.getPosition(),projectile.getRadius())) {
                        std::cout << "Hit target " << i + 1 << "!\n";
                        target->setDestroyed(true);
                        currentPlayer.addScore(10);
                        projectile.reset(); // stop further movement
                        break;
                    }
                }

                if (!projectile.isActive()) break;
            }

            // Check if all targets destroyed
            levelComplete = true;
            for (int i = 0; i < level.getTargetCount(); ++i) {
                if (!level.getTarget(i)->isDestroyed()) {
                    levelComplete = false;
                    break;
                }
            }

            playerTurn = (playerTurn + 1) % 2;
        }

        std::cout << "Level " << currentLevel << " complete!\n";
        if (p1.getTries() < p2.getTries()) {
            std::cout << p1.getName() << " wins this level!\n";
        }
        else if (p2.getTries() < p1.getTries()) {
            std::cout << p2.getName() << " wins this level!\n";
        }
        else {
            std::cout << "It's a tie on this level!\n";
        }
        p1.resetTries();
        p2.resetTries();

        currentLevel++;
    }

    // Final scores
    std::cout << "Final Scores:\n";
    for (int i = 0; i < engine.getPlayerCount(); ++i) {
        const Player& p = engine.getPlayer(i);
        std::cout << p.getName().returnArray() << ": " << p.getScore() << "\n";
    }

    return 0;
}
