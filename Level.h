#ifndef LEVEL_H
#define LEVEL_H// include/Level.h
#include "Target.h"
#include "MyVector.h"
#include "XYCoord.h"
#include "Obstacle.h"
class Level {
public:

	Level(int levelNum = 1);
	~Level();

	// Remove all targets & obstacles.
	void clear();
	void setWind(const XYCoord& w) { wind = w; }

	void addTarget(Target* t) { targets.push(t); }
	void addObstacle(Obstacle* o) { obstacles.push(o); }
	void update(float dt);

	bool isCompleted() const;
	const Dynamic_array<Target*>& getTargets() const { return targets; }
	XYCoord getWind() const { return wind; }
	int getLevelNumber() const { return levelNumber; }
private:
	int                   levelNumber;
	Dynamic_array<Target*>     targets;
	Dynamic_array<Obstacle*>   obstacles;
	XYCoord               wind;
};
#endif