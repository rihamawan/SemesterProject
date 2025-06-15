#include "GameEngine.h"
#include <iostream>
using namespace std;
GameEngine::GameEngine(const MyString& levelPath, const MyString& saveFilePath, const MyString& logFilePath) : logger(logFilePath), levelManager(levelPath, logger), stateManager(saveFilePath){}

void GameEngine::init() {
    players.clear();
    players.push(Player("Player1", XYCoord(100, 0)));
    players.push(Player("Player2", XYCoord(900, 0)));
    currentPlayerIndex = 0;

    projectiles.clear();
    shotFired = false;
    quitRequested = false;

    loadLevel(1);
}

void GameEngine::run() {
    const float dt = 1.0f / 60.0f;  
    try {
        while (!quitRequested) {
            update(dt);
            draw();
        }
    }
    catch (GameException& e) {
        logger.logError(e.getMessage());
    }
}

void GameEngine::update(float dt) {
    if (!shotFired) {
        handleInput();
    }
    else {
        for (auto& proj : projectiles) {
            proj.update(dt, level.getWind());
        }

        if (projectiles.empty()) {
            shotFired = false;

            if (level.isCompleted()) {
                stateManager.save(*this);
                loadLevel(getCurrentLevelNumber() + 1);
            }
            else {
                currentPlayerIndex = 1 - currentPlayerIndex;
            }
        }
    }
}

void GameEngine::draw() const {
    std::cout<< "Level " << getCurrentLevelNumber()
        << " | " << players[0].getName() << " score=" << players[0].getScore()
        << " | " << players[1].getName() << " score=" << players[1].getScore()
        << " | " << players[currentPlayerIndex].getName() << "'s turn\n";
}

void GameEngine::handleInput() {
    Player player = players[currentPlayerIndex];
    cout<< player.getName()<< " — enter angle power, or 'save', 'quit': ";

    char line[7];
    if (!cin.getline(line,7)) {
        quitRequested = true;
        stateManager.save(*this);
        return;
    }

    if (line == "quit") {
        quitRequested = true;
        stateManager.save(*this);
        return;
    }
    if (line == "save") {
        stateManager.save(*this);
        return;
    }

    MyString inputLine(line);                  
    int partCount = 0;
    MyString* parts = inputLine.split(' ', partCount);

    if (partCount != 2) {
        cout << "Invalid input—please enter angle and power.\n";
        delete[] parts; 
        return;
    }

    float angle = parts[0].toFloat();  
    float power = parts[1].toFloat(); 

    delete[] parts; 


    player.setAngle(angle);
    player.setPower(power);

    projectiles.push(player.fire());
    shotFired = true;
}

int GameEngine::getCurrentLevelNumber() const {
    return level.getLevelNumber();
}

void GameEngine::loadLevel(int levelNumber) {
    levelManager.loadLevel(levelNumber, level);
}

Dynamic_array<Player>& GameEngine::getPlayers() { return players; }
const Dynamic_array<Player>& GameEngine::getPlayers() const { return players; }

Level& GameEngine::getLevel() { return level; }
const Level& GameEngine::getLevel() const { return level; }

XYCoord GameEngine::getPlayerStartPosition(int idx) const {
    if (idx < players.size()) return players[idx].getPosition();
    return XYCoord{};
}
