#include "monster.h"

monster::~monster() {}

void monster::move(float delta)
{
    int random = std::rand() % 4 + 1;
	int x, y;
	switch (random) {
	case 1:
		x = this->getSprite()->getPositionX() + 10;
		y = this->getSprite()->getPositionY();
		if (x > 10 && x < 1024 && y>10 && y < 768)
		{
			this->getSprite()->setPosition(x, y);
			break;
		}
	case 2: 
		x = this->getSprite()->getPositionX() - 10;
		y = this->getSprite()->getPositionY();
		if (x > 10 && x < 1024 && y>10 && y < 768)
		{
			this->getSprite()->setPosition(x, y);
			break;
		}
	case 3: 
		x = this->getSprite()->getPositionX();
		y = this->getSprite()->getPositionY() + 10;
		if (x > 10 && x < 1024 && y>10 && y < 768)
		{
			this->getSprite()->setPosition(x, y);
			break;
		}
	case 4: 
		x = this->getSprite()->getPositionX();
		y = this->getSprite()->getPositionY() - 10;
		if (x > 10 && x < 1024 && y>10 && y < 768)
		{
			this->getSprite()->setPosition(x, y);
			break;
		}
	}
}

void monster::bindAtBattleRoom(Scene* scene) {
	this->atBattleRoom = scene; 
}

Scene* monster::getAtBattleRoom() const { return this->atBattleRoom; }

void monster::setIsAdded(bool status) { this->isAdded = status; }

bool monster::getIsAdded() const { return this->isAdded; }

bool monster::init() {
	isAdded = false;
	auto monsterSP = Sprite::create("Enemy//Ice//enemy007.png");
	bindSprite(monsterSP);
	this->schedule(CC_SCHEDULE_SELECTOR(monster::move),0.3f);
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