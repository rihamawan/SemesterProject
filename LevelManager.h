#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H
#include "Level.h"
#include "Logger.h"
#include "MyString.h"

//Loads level definitions from binary files into Level instances.
class LevelManager {
public:
    LevelManager(/*const MyString& basePath,*/ Logger& logger);
    void loadLevel(int levelNumber, Level& level);

private:
    //MyString   basePath;
    Logger& logger;
    MyString buildFilePath(int levelNumber) const;
};
#endif