#include "Protestor.h"
#include "StudentWorld.h"

RegularProtestor::RegularProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth), tickCounter(0), direction_integer(0)
{
	setDirection(left);
	leaveOilFieldState = false;
	setHealth(5);
	srand(time(NULL));
	numSquaresMovedInCurrentDirection = 0;
	my_min = rand() % (60 - getX() + 1) + 15;
}

void RegularProtestor::setLeaveOilFieldState(bool state)
{
	leaveOilFieldState = state;
}

bool RegularProtestor::getLeaveOilFieldState()
{
	return leaveOilFieldState;
}
void RegularProtestor::setTickCounter(int tickCounter_)
{
	tickCounter = tickCounter_;
}

void RegularProtestor::leaveOilField()
{

}
void RegularProtestor::doSomething()
{
	if (!getAlive()) return;//return if not alive

	if (leaveOilFieldState == true)
	{
		leaveOilField();
		return;
	}

	if (getHealth() == 0)//this should only happen once in a protestor's life
	{
		leaveOilFieldState = true;
		getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
		tickCounter = 0;
	}

	if (tickCounter > 0)
	{
		tickCounter--;//decriment tick
		return;
	}

	//protestor is alive and able to move, therefore tick countrer should be set back to the level's correct value max(0,3-lvl)
	setTickCounter(max(0, 3));//placehold value

	if (!getLeaveOilFieldState())//protester is moving freely
	{
		if (canMovePerpendicular()) return;
		wander();
		numSquaresMovedInCurrentDirection++;
	}


}

bool RegularProtestor::canMovePerpendicular()
{
	return 0;//temp
	int x = getX(), y = getY();

	if (getDirection() == left)
	{
		if (!getWorld()->getDirt(getX() - 1, getY() - 1)->getAlive()
			&& !getWorld()->getDirt(getX() - 2, getY() - 1)->getAlive()
			&& !getWorld()->getDirt(getX() + 1, getY() - 1)->getAlive()
			&& !getWorld()->getDirt(getX() + 1, getY() - 1)->getAlive())
		{

			moveTo(getX(), getY());
			//moveTo(getX(), getY()-1);
			setDirection(down);
			//numSquaresMovedInCurrentDirection = rand() % 58 + 6;
			return 1;
		}
	}
	else if (getDirection() == right)
	{

	}
	else if (getDirection() == up)
	{

	}
	else if (getDirection() == down)
	{

	}
	return 0;
}
void RegularProtestor::move(GraphObject::Direction direction) {
	int x = getX();
	int y = getY();
	if (direction == left)
		moveTo(x - 1, y);
	if (direction == right)
		moveTo(x + 1, y);
	if (direction == up)
		moveTo(x, y + 1);
	if (direction == down)
		moveTo(x, y - 1);
}
void RegularProtestor::wander()
{
	GraphObject::Direction direction = getDirection();
	//want to wander where it only turns to a place with no dirt
	int x = getX();
	int y = getY();
	bool directions[4] = { false };
	//i think the best way to do this is to check around all 4 directions and then if there is a path then randomly go down one of those instead of
	//checking each direction one at a time and going to one of them because then all of the protestors will go in the same direction
	if (!isDirtThere(x, y, left) && x > 0) {
		directions[0] = true;
	}
	if (!isDirtThere(x + 3, y, right) && x < 60) {
		directions[1] = true;
	}
	if (!isDirtThere(x, y + 3, up) && y < 60) {
		directions[2] = true;
	}
	if (!isDirtThere(x, y, down) && y > 0) {
		directions[3] = true;
	}
	vector<int> options;
	for (int i = 0; i < 4; i++) {
		if (directions[i] == true)
			options.push_back(i);
	}

	direction_integer = rand() % options.size();

	direction_integer = options[direction_integer];

	if (direction_integer == 0 && x > 0) {
		if (direction == left)
			move(left);
		else if (direction != left && numSquaresMovedInCurrentDirection > my_min || isDirtThere(x, y, direction)) {
			setDirection(left);
			move(left);
			numSquaresMovedInCurrentDirection = 0;
			my_min = rand() % 60 + 15;
		}
		else
			move(direction);
	}

	else if (direction_integer == 1 && x < 60) {//right
		if (direction == right)
			move(right);
		else if (direction != right && numSquaresMovedInCurrentDirection > my_min || isDirtThere(x, y, direction)) {
			setDirection(right);
			move(right);
			numSquaresMovedInCurrentDirection = 0;
			my_min = rand() % 60 + 15;
		}
		else
			move(direction);
	}
	else if (direction_integer == 2 && y < 60) {//up
		if (direction == up)
			move(up);
		else if (direction != up && numSquaresMovedInCurrentDirection > my_min || isDirtThere(x, y, direction)) {
			setDirection(up);
			move(up);
			numSquaresMovedInCurrentDirection = 0;
			my_min = rand() % 60 + 15;
		}
		else
			move(direction);
	}
	else if (direction_integer == 3 && y > 0) {// down
		if (direction == down)
			move(down);
		else if (direction != down && numSquaresMovedInCurrentDirection > my_min || isDirtThere(x, y, direction)) {
			setDirection(down);
			move(down);
			numSquaresMovedInCurrentDirection = 0;
			my_min = rand() % 60 + 15;
		}
		else
			move(direction);
	}

}

RegularProtestor::~RegularProtestor()
{

}