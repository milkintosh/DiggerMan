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
public:

	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init();
	
	virtual int move();

	virtual void cleanUp();

	void addBoulders();

	void addDirt();
	
	void removeDirt();

	bool checkUnder(Boulder * b);

	bool isThere();

	vector<Actor*> getActors() {
		return actors;
	}

	void removeDead(vector<Actor*>& actor);

	void setDisplayText();

};

#endif // STUDENTWORLD_H_
