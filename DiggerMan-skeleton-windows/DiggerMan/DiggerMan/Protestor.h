#ifndef PRO
#define PRO

#include "Actor.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <time.h>
using namespace std;

class RegularProtestor : public Actor
{
private:
	bool leaveOilFieldState;
	int numSquaresMovedInCurrentDirection;
	int tickCounter;
	int direction_integer;
	int my_min;
public:
	void move(GraphObject::Direction);
	RegularProtestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	bool getLeaveOilFieldState();
	void setLeaveOilFieldState(bool);
	void setTickCounter(int);
	int getTickCounter() { return tickCounter; }
	void wander();
	void switchDirection(int);
	void leaveOilField();
	bool canMovePerpendicular();
	//void movePerpendicular();
	//bool isDirtThere();
	~RegularProtestor();
};

#endif