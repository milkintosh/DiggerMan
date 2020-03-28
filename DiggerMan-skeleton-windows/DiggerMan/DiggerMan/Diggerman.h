#ifndef DIG_MAN
#define DIG_MAN
#include "Actor.h"

class DiggerMan : public Actor
{
private:
	Actor *parent;
public:
	DiggerMan(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	Actor * getParent() { return parent; }
	~DiggerMan();
};

#endif