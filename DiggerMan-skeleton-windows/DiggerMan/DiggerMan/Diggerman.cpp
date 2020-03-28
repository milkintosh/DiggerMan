#include "Diggerman.h"
#include "StudentWorld.h"

DiggerMan::DiggerMan(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(p, imageID, startX, startY, dir, size, depth) {
}

DiggerMan::~DiggerMan() {}

void DiggerMan::doSomething()
{
	int x = getX();
	int y = getY();
	int ch;
	if (getAlive()) {
		if (getWorld()->getKey(ch) == true) {
			switch (ch) {
			case KEY_PRESS_LEFT:
				if (getDirection() != left) {
					setDirection(left);
					break;
				}
				else {
					setDirection(left);
					if (x < 1)
						break;
					if (!getWorld()->isThere()) {
						moveTo(x - 1, y);
					}
					if (getWorld()->removeDirt()) {
						getWorld()->playSound(SOUND_DIG);
					}
					break;
				}
			case KEY_PRESS_RIGHT:
				if (getDirection() != right) {
					setDirection(right);
					break;
				}
				else {
					setDirection(right);
					if (x > 59)
						break;
					if (!getWorld()->isThere()) {
						moveTo(x + 1, y);
					}
					if (getWorld()->removeDirt()) {
						getWorld()->playSound(SOUND_DIG);
					}
					break;
				}
			case KEY_PRESS_UP:
				if (getDirection() != up) {
					setDirection(up);
					break;
				}
				else {
					setDirection(up);
					if (y > 59)
						break;
					if (!getWorld()->isThere()) {
						moveTo(x, y + 1);
					}
					if (getWorld()->removeDirt())
						getWorld()->playSound(SOUND_DIG);
					break;
				}
			case KEY_PRESS_DOWN:
				if (getDirection() != down) {
					setDirection(down);
					break;
				}
				else {
					setDirection(down);
					if (y < 1)
						break;
					if (!getWorld()->isThere()) {
						moveTo(x, y - 1);
					}
					if (getWorld()->removeDirt()) {
						getWorld()->playSound(SOUND_DIG);
					}
					break;
				}
			case 'z':
				if (getWorld()->getSonar() > 0) {
					getWorld()->setallVisible();
					getWorld()->decSonar();
				}
				break;
			case 'Z':
				if (getWorld()->getSonar() > 0) {
					getWorld()->setallVisible();
					getWorld()->decSonar();
				}
				break;
			case KEY_PRESS_ESCAPE:
				setAlive(false);
				break;
			case KEY_PRESS_SPACE: //this is where he shoots water
				if (getWorld()->decWater()) {
					//if a protestor is in front of the diggerman and is (a space?)
					//away from the diggerman, (stun him and lower his health?)
				}
				break;
				setAlive(false);
				break;
			case KEY_PRESS_TAB: //the diggerman can drop gold and bribe the protestors. 
				//regular protestors will take the bribe and go out of the map
				//if nobody picks up the gold in a certain amount of time, the gold will disappear
				getWorld()->dropGold();
			}
		}
	}
	else
		return;

}