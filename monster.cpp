#include "monster.h"
#include "battleRoom.h"

monster::~monster() {}


int monster::getmydamage()const
{
	return (this->_damage);
}
void monster::dead()
{
	this->setHP(-1);
}

void monster::move(float delta)
{
	if (!this->isdead()&&!this->canattack)
	{
		auto moveby1 = MoveBy::create(1.0, Vec2(5 * _moveSpeed, 0));
		auto moveby2 = MoveBy::create(1.0, Vec2(-5 * _moveSpeed, 0));
		auto moveby3 = MoveBy::create(1.0, Vec2(0, 5 * _moveSpeed));
		auto moveby4 = MoveBy::create(1.0, Vec2(0, -5 * _moveSpeed));

		auto moveby5 = MoveBy::create(1.0, Vec2(3 * _moveSpeed, 0));
		auto moveby6 = MoveBy::create(1.0, Vec2(-3 * _moveSpeed, 0));
		auto moveby7 = MoveBy::create(1.0, Vec2(0, 3 * _moveSpeed));
		auto moveby8 = MoveBy::create(1.0, Vec2(0, -3 * _moveSpeed));

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
			if (this->gettype() == 0)
			{
				x += 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby1);
				}
			}
			if (this->gettype() == 1)
			{
				x += 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby5);
				}
			}
			break;
		case 2:
			if (this->gettype() == 0)
			{
				x -= 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby2);
				}
			}
			if (this->gettype() == 1)
			{
				x -= 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby6);
				}
			}
			break;
		case 3:
			if (this->gettype() == 0)
			{
				y += 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby3);
				}
			}
			if (this->gettype() == 1)
			{
				y += 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby7);
				}
			}
			break;
		case 4:
			if (this->gettype() == 0)
			{
				y -= 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby4);
				}
			}
			if (this->gettype() == 1)
			{
				y -= 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby8);
				}
			}
			break;
		}
	}
}

void monster::bindAtBattleRoom(battleRoom* curBattleRoom) {
	this->atBattleRoom = curBattleRoom;
}

battleRoom* monster::getAtBattleRoom() const { return this->atBattleRoom; }

void monster::setIsAdded(bool status) { this->isAdded = status; }

bool monster::getIsAdded() const { return this->isAdded; }

bool monster::init() {
	isAdded = false;
	this->settype();
	this->setAttackRange();
	int curtype = this->gettype();
	if (curtype == 0)
	{
		auto monsterSP = Sprite::create("Enemy//Forest//enemy007.png");
		bindSprite(monsterSP);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
	}
	if (curtype == 1)
	{
		auto monsterSP = Sprite::create("Enemy//Forest//enemy002.png");
		bindSprite(monsterSP);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
	}
	return true;
}

void monster::setAttackRange() {
	switch (enemyType)
	{
	case 0:
		ATTACKRANGE = 200;
		break;
	case 1:
		ATTACKRANGE = 400;
		break;
	}
}

int monster::getAttackRange()const
{
	return ATTACKRANGE;
}

void monster::settype()
{
	int random = rand() % 2;
	enemyType = random;
}

int monster::gettype()const
{
	return enemyType;
}