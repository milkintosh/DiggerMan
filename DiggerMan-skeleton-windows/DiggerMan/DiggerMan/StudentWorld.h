#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <algorithm>
#include<cmath>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld : public GameWorld
{
private:
	Actor* m_diggerman;
	Dirt* dirtarr[64][60];
	vector<Actor*> actors;
	int m_barrels;
	//Actor* m_protestorTest;//for testing protestor funtions, will be deleted later
	//Actor* m_protestorTest2;//for testing protestor funtions, will be deleted later
public:

	StudentWorld(std::string assetDir)
		: GameWorld(assetDir),m_barrels(0)
	{
	}

	virtual int init();
	
	virtual int move();

	virtual void cleanUp();

	void addBoulders();

	void addActors(Actor* actor);
	
	bool isClose();

	void isTouching();

	void addDirt();
	
	void removeDirt();

	bool checkUnder(Boulder * b);

	bool isThere();

	vector<Actor*> getActors() {
		return actors;
	}

	void removeDead();

	void setDisplayText();

	Actor* getDiggerman();

	int getBarrels();

	void decBarrels() { m_barrels--; return; }
	bool checkDistance(int x, int y);
	void addGoldNuggets();
	void addBarrel();

};

#endif // STUDENTWORLD_H_
