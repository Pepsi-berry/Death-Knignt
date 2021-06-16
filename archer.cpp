#include "archer.h"
#include "battleRoom.h"

archer::~archer() {}


int archer::getmydamage()const
{
	return (this->_damage);
}
void archer::dead()
{
	this->setHP(-1);
}

void archer::move(float delta)
{
	if (!this->isdead() && !this->canattack)
	{
		auto moveby1 = MoveBy::create(1.0, Vec2(5 * _moveSpeed, 0));
		auto moveby2 = MoveBy::create(1.0, Vec2(-5 * _moveSpeed, 0));
		auto moveby3 = MoveBy::create(1.0, Vec2(0, 5 * _moveSpeed));
		auto moveby4 = MoveBy::create(1.0, Vec2(0, -5 * _moveSpeed));

		auto winSize = Director::getInstance()->getVisibleSize();
		Vec2 me_size = this->getContentSize();
		//int Xmin = me_size.x;
		//int Ymin = me_size.y;
		//int Xmax = winSize.width;
		//int Ymax = winSize.height;
		float Xmin = this->getAtBattleRoom()->getTopLeftCornerPositionX();
		float Ymin = this->getAtBattleRoom()->getLowerRightCornerPositionY();
		float Xmax = this->getAtBattleRoom()->getLowerRightCornerPositionX();
		float Ymax = this->getAtBattleRoom()->getTopLeftCornerPositionY();



		int x, y;
		x = this->getPositionX();
		y = this->getPositionY();

		int random = std::rand() % 4 + 1;
		switch (random) {
		case 1:
			x += 3 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby1);
			}
			break;
		case 2:
			x -= 3 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby2);
			}
			break;
		case 3:
			y += 3 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby3);
			}
			break;
		case 4:
			y -= 3 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby4);
			}
			break;
		}
	}
}

void archer::bindAtBattleRoom(battleRoom* curBattleRoom) {
	this->atBattleRoom = curBattleRoom;
}

battleRoom* archer::getAtBattleRoom() const { return this->atBattleRoom; }

void archer::setIsAdded(bool status) { this->isAdded = status; }

bool archer::getIsAdded() const { return this->isAdded; }

bool archer::init() {
	isAdded = false;
	auto archerSP = Sprite::create("Enemy//Forest//enemy002.png");
	bindSprite(archerSP);
	this->schedule(CC_SCHEDULE_SELECTOR(archer::move), 1.0f);
	return true;
}