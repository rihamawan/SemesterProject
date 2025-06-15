#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H
#include "MyString.h"

class GameEngine;

// Handles saving/loading game state to a binary file.
class StateManager {
public:
    explicit StateManager(const MyString& filePath);

    void save(const GameEngine& engine);
    void load( GameEngine& engine);

private:
    MyString saveFilePath;
};
#endif
