#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "MyVector.h"
#include "Player.h"
#include "Projectile.h"
#include "Level.h"
#include "LevelManager.h"
#include "StateManager.h"
#include "Logger.h"
#include "GameException.h"
class GameEngine {
public:
    GameEngine(const MyString& levelPath, const MyString& saveFilePath,const MyString& logFilePath);
    void init();
    void run();
    int getCurrentLevelNumber() const;
    // (Re)load the given level number
    void loadLevel(int levelNumber);
    Player& getPlayer(int index);
    int getPlayerCount() const;
    void addPlayer(const Player& player);
    Dynamic_array<Player>& getPlayers();
    const Dynamic_array<Player>& getPlayers() const;

    Level& getLevel();
    const Level& getLevel() const;

    XYCoord getPlayerStartPosition(int index) const;

private:
    void update(float dt);
    void draw() const;
    void handleInput();
    Dynamic_array<Player>     players;
    Dynamic_array<Projectile> projectiles;
    Level                level;
    Logger               logger;
    LevelManager         levelManager;
    StateManager         stateManager;
    int               currentPlayerIndex = 0;
    bool                 quitRequested = false;
    bool                 shotFired = false;
};

#endif