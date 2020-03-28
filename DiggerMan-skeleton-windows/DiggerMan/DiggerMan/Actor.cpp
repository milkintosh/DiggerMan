#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <time.h>
using namespace std;


//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Actor::Actor(StudentWorld *p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : 
	GraphObject(imageID, startX, startY, dir, size, depth), isAlive(true), world(p), health(100)
{
	setVisible(true);
	setAlive(true);
}

Actor::~Actor(){}
 
void Actor::doSomething(){}

bool Actor::getAlive() {
	return isAlive;
}
void Actor::setAlive(bool Is) {
	isAlive = Is;
}
StudentWorld *Actor::getWorld() {
	return world;
}

void Actor::setHealth(int health_) {
	health = health_;
}

bool Actor::isDirtThere(int x, int y, GraphObject::Direction direction) {

	if (direction == left) {
		if (x > 0) {
			if (y < 57)
			{
				if ((getWorld()->getDirt(x - 1, y)->getAlive())
					|| (getWorld()->getDirt(x - 1, y + 1)->getAlive())
					|| (getWorld()->getDirt(x - 1, y + 2)->getAlive())
					|| (getWorld()->getDirt(x - 1, y + 3)->getAlive()))
					return true;
			}
			else if (y == 57) {
				if (getWorld()->getDirt(x - 1, y)->getAlive()
					|| getWorld()->getDirt(x - 1, y + 1)->getAlive()
					|| getWorld()->getDirt(x - 1, y + 2)->getAlive())
					return true;
			}
			else if (y == 58) {
				if (getWorld()->getDirt(x - 1, y)->getAlive()
					|| getWorld()->getDirt(x - 1, y + 1)->getAlive())
					return true;
			}
			else if (y == 59) {
				if (getWorld()->getDirt(x - 1, y)->getAlive())
					return true;
			}
		}
		else return true;
	}
	else if (direction == right) {
		if (x < 60) {
			if (y < 57) {
				if ((getWorld()->getDirt(x + 1, y)->getAlive())
					|| (getWorld()->getDirt(x + 1, y + 1)->getAlive())
					|| (getWorld()->getDirt(x + 1, y + 2)->getAlive())
					|| (getWorld()->getDirt(x + 1, y + 3)->getAlive()))
					return true;
			}
			else if (y == 57) {
				if (getWorld()->getDirt(x + 1, y)->getAlive()
					|| getWorld()->getDirt(x + 1, y + 1)->getAlive()
					|| getWorld()->getDirt(x + 1, y + 2)->getAlive())
					return true;
			}
			else if (y == 58) {
				if (getWorld()->getDirt(x + 1, y)->getAlive()
					|| getWorld()->getDirt(x + 1, y + 1)->getAlive())
					return true;
			}
			else if (y == 59) {
				if (getWorld()->getDirt(x + 1, y)->getAlive())
					return true;
			}
		}
		else return true;
	}
	else if (direction == down) {
		if (y > 0) {
			if ((getWorld()->getDirt(x, y - 1)->getAlive())
				|| (getWorld()->getDirt(x + 1, y - 1)->getAlive())
				|| (getWorld()->getDirt(x + 2, y - 1)->getAlive())
				|| (getWorld()->getDirt(x + 3, y - 1)->getAlive()))
				return true;
		}
		else return true;
	}
	else if (direction == up) {
		if (y < 60)
		{
			if ((getWorld()->getDirt(x, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 1, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 2, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 3, y + 1)->getAlive()))
				return true;
		}
		else return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////  DIRT    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Dirt::Dirt(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth){}

Dirt::~Dirt(){}

void Dirt::doSomething(){}

//////////////////////////////////////////////////////////////  BOULDER  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Boulder::Boulder(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth),count(0),fell(false) {}

Boulder::~Boulder(){}

void Boulder::doSomething() {
	if (getAlive())
	{
		int x = getX();
		int y = getY(); 
		if (y == 0) {

			setVisible(false);
			setAlive(false);

		}
		if (y < 60 && y>0)//check under the boulder only if it's inside the map
		{
			if (getWorld()->checkUnder(this)) {
				count++;
				if (count >= 30) {//30 ticks have to pass before the boulder falls
					if (fell==false)//if this is the first time the boulder has moved at all
						getWorld()->playSound(SOUND_FALLING_ROCK);//play the sound once
					moveTo(x, y - 1);
					int BX = getWorld()->getDiggerman()->getX();
					int BY = getWorld()->getDiggerman()->getY();
					double SR = pow((pow(abs(x - BX), 2) + pow(y - BY, 2)), 0.5);
					if (SR <= 3.0) {
						getWorld()->getDiggerman()->setVisible(false); //this is when the diggerman gets hit by the boulder, use this to check protestors as well
						getWorld()->getDiggerman()->setAlive(false);
					}
					//getWorld()->BoulderHitDig();
					fell = true;//this also helps get rid of the boulder
				}
			}
			else if (fell == true){ //if the boulder has fallen
				setVisible(false);
				setAlive(false);
			}
			else
				return;
		}
	}
	else 
		return;
}
////////////////////////////////////////////////////////////// GoldNugget  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GoldNugget::GoldNugget(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth), pickUpProtestor(false), pickUpDiggerman(false)
{
	setVisible(false);
}
void GoldNugget::doSomething()
{
	if (getAlive())
	{
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		if (SR != 0 && !pickUpProtestor) {
			if (SR <= 4.0 && !pickUpDiggerman && !pickUpProtestor) {// can we leave this value so its easier to see the objects when we get close
				// you can change it back when we turn it in
				pickUpDiggerman = true;
				setVisible(true);
				return;
			}
			if (SR <= 3.0 && pickUpDiggerman && !pickUpProtestor) {
				setVisible(true);
				setVisible(false);
				setAlive(false);
				getWorld()->increaseScore(10);
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->incGold();
				pickUpDiggerman = false;
			}
		}
		else {
			pickUpProtestor = true;
			if (getWorld()->pickUPPRO(x, y)){
				getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
				setVisible(false);
				setAlive(false);
			}
		}
	}
		else
			return;
}
GoldNugget::~GoldNugget() {}


//////////////////////////////////////////////////////////////  OIL  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Oil::Oil(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),pick(false) {
	setVisible(false);
}

void Oil::doSomething() {
	if (getAlive())
	{
		
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		if (SR <= 4.0 && !pick) { // can we leave this value so its easier to see the objects when we get close
									// you can change it back when we turn it in
			pick = true;
			setVisible(true);
			return;
		}
		if (SR <= 3.0 &&pick) {
			setVisible(true);
			setVisible(false);
			setAlive(false);
			getWorld()->decBarrels();
			getWorld()->playSound(SOUND_FOUND_OIL);
			getWorld()->increaseScore(1000);
			pick = false;
		}
	}
	else 
		return;
}
Oil::~Oil() {}

//////////////////////////////////////////////////////////////  SONAR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sonar::Sonar(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth),count(0) {}

void Sonar::doSomething() {
	if (getAlive()) {
		count++;
        int x = getX();
        int y = getY();
        int digX = getWorld()->getDiggerman()->getX();
        int digY = getWorld()->getDiggerman()->getY();
        double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
        int current_level = getWorld()->getLevel();
		int a = max(100, 300 - 10 * current_level);
		if (SR <= 3) {
			setVisible(false);
			setAlive(false);
			getWorld()->decSonarInMap();
			getWorld()->incSonar();
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(75);
		}
		else if (count == a) {
			setVisible(false);
			setAlive(false);
			getWorld()->decSonarInMap();
		}
	}
	else return;
}

Sonar::~Sonar() {}

//////////////////////////////////////////////////////////////  WATERPOOLS  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Water::Water(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth),count(0) {}

void Water::doSomething() {
	if (getAlive()) {
		count++;
		int x = getX(), y = getY(), 
			digX = getWorld()->getDiggerman()->getX(), 
			digY = getWorld()->getDiggerman()->getY(),
			current_level = getWorld()->getLevel(),
			a = max(100, 300 - 10 * current_level);
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5); //this is a distance formula
		if (SR <= 3) {
			setVisible(false);
			setAlive(false);
			getWorld()->decWaterInMap();
			getWorld()->incWater();
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(100);
		}
		else if (count == a) {
			setVisible(false);
			setAlive(false);
			getWorld()->decWaterInMap();
		}
	}
	else return;
}

Water::~Water() {}

//////////////////////////////////////////////////////////////  SQUIRT  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Squirt::Squirt(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth) {}

void Squirt::doSomething() {
	cout << "i this spacebar?";
	//if protestor is near, then do something to them. 
	//decrease the amount of water on the player
}

Squirt::~Squirt() {}

////////////////////////////////////////////////////////////// HARDCORE PROTESTOR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//HardcoreProtestor::HardcoreProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : RegularProtestor(p, imageID, startX, startY, dir, size, depth)
//{
//	setHealth(20);
//}
//
//
//void HardcoreProtestor::doSomething()
//{
//
//}
//
//
//HardcoreProtestor::~HardcoreProtestor()
//{
//
//}
