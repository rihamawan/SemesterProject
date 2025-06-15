#include "Level.h"
#include "StaticTarget.h"
#include "MovingTarget.h"

Level::Level(int levelNum)
    : levelNumber(levelNum), wind(0, 0)
{}
Level::~Level() {
    clear();
}

void Level::clear() {
    for (auto t : targets)    delete t;
    for (auto o : obstacles) delete o;
    targets.clear();
    obstacles.clear();
}

void Level::update(float dt) {
    for (auto t : targets) {
        t->update(dt);
    }
}

bool Level::isCompleted() const {
    for (auto t : targets) {
        if (!t->isDestroyed()) return false;
    }
    return true;
}

void Level::draw() const {
    for (int i = 0; i < targets.size(); ++i)
        targets[i]->draw();

    for (int i = 0; i < obstacles.size(); ++i)
        obstacles[i]->draw();
}
