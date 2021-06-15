#include "monster.h"

monster::~monster() {}

void monster::dead()
{
	this->setHP(-1);
}

void monster::move(float delta)
{
	if (!this->isdead())
	{
		auto moveby1 = MoveBy::create(1.0, Vec2(5 * _moveSpeed, 0));
		auto moveby2 = MoveBy::create(1.0, Vec2(-5 * _moveSpeed, 0));
		auto moveby3 = MoveBy::create(1.0, Vec2(0, 5 * _moveSpeed));
		auto moveby4 = MoveBy::create(1.0, Vec2(0, -5 * _moveSpeed));

		auto winSize = Director::getInstance()->getVisibleSize();
		Vec2 me_size = this->getContentSize();
		int Xmin = me_size.x;
		int Ymin = me_size.y;
		int Xmax = winSize.width;
		int Ymax = winSize.height;

		int x, y;
		x = this->getPositionX();
		y = this->getPositionY();

		int random = std::rand() % 4 + 1;
		switch (random) {
		case 1:
			x += 5 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby1);
			}
			break;
		case 2:
			x -= 5 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby2);
			}
			break;
		case 3:
			y += 5 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby3);
			}
			break;
		case 4:
			y -= 5 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby4);
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
	auto monsterSP = Sprite::create("Enemy//Forest//enemy007.png");
	bindSprite(monsterSP);
	this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
	return true;
}

void monster::setAttackRange() {
	switch (enemyType)
	{
	case 0:
		ATTACKRANGE = 280;
		break;
	case 1:
		ATTACKRANGE = 50;
		break;
	}
}