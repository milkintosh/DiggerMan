#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "Diggerman.h"
#include "Protestor.h"
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
    int m_gold;
	int m_sonar;
	int m_water;
	int m_protestors = 0;
	int sonarInMap = 0;
	int waterInMap = 0;
	int tickCount=0;
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir),m_barrels(0),m_gold(3),m_sonar(1), m_water(5)//starts with one sonar, specs
	{
	}

	virtual int init();
	
	virtual int move();

	virtual void cleanUp();

	void addBoulders();

	void addSonarKit();

	void addWater();

	bool isBoulderThere();

	void addDirt();
	
	bool removeDirt();

	bool checkUnder(Boulder * b);

	bool isThere();
	Dirt* getDirt(int x, int y)
	{
		return dirtarr[x][y];
	}

	vector<Actor*> getActors() {
		return actors;
	}

	void removeDead();

	void setDisplayText();
    
    void setallVisible();

    Actor* getDiggerman(){ return m_diggerman; }

	int getSonar() { return m_sonar; }
    
    void incGold(){ m_gold++; return; }

	void decBarrels() { m_barrels--; return; }

	void incSonar() { m_sonar++; }
	bool decSonar() {
		if (m_sonar > 0) {
			m_sonar--;
			return true;
		}
		return false;
	}
	void decSonarInMap() { sonarInMap--; }

	void incWater() { m_water+=5; }
	bool decWater() {
		if (m_water > 0) {
			m_water--;
			return true;
		}
		return false;
	}
	void decWaterInMap() { waterInMap--; }

	bool checkDistance(int x, int y);
	void addGoldNuggets();
	void addBarrel();
	void addProtestors();
	void dropGold();
	bool pickUPPRO(int x, int y);
};

#endif // STUDENTWORLD_H_
