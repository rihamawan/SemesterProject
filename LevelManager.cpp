#include "LevelManager.h"
#include <fstream>
#include "StaticTarget.h"
#include "MovingTarget.h"
#include "RectangularObstacle.h"
#include "CircularObstacle.h"

LevelManager::LevelManager(/*const MyString& basePath_,*/ Logger& logger_) : /*basePath(basePath_),*/ logger(logger_) {}

MyString LevelManager::buildFilePath(int levelNumber) const {
    return /*basePath.concat*/MyString("level").concat(MyString::itos(levelNumber)).concat(".txt");
}

void LevelManager::loadLevel(int levelNumber, Level& level) {
    MyString path = buildFilePath(levelNumber);
    ifstream in(path.returnArray());
    logger.logError(MyString("Cannot open level file: ").concat(path));
    throw FileIOException(MyString("Cannot open level file: ").concat(path));

    float wx, wy;
    in >> wx >> wy;
    level.setWind(XYCoord(wx, wy));

    int targetCount;
    in >> targetCount;

    for (int i = 0; i < targetCount; ++i) {
        float x, y, w, h;
        int isMoving;
        in >> x >> y >> w >> h >> isMoving;

        if (isMoving) {
            float dirX, dirY, speed;
            in >> dirX >> dirY >> speed;
            level.addTarget(new MovingTarget(XYCoord(x, y), w, h, speed,XYCoord(dirX,dirY)));
        }
        else {
            level.addTarget(new StaticTarget(XYCoord(x, y), w, h));
        }
    }

    int obstacleCount;
    in >> obstacleCount;

    for (int i = 0; i < obstacleCount; ++i) {
        float x, y;
        int type;
        in >> x >> y >> type;

        if (type == 0) {
            float ow, oh;
            in >> ow >> oh;
            level.addObstacle(new RectangularObstacle(XYCoord(x, y), ow, oh));
        }
        else {
            float r;
            in >> r;
            level.addObstacle(new CircularObstacle(XYCoord(x, y), r));
        }
    }
}
