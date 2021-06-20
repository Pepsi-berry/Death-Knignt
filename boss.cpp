#include "boss.h"
#include "battleRoom.h"

boss::~boss() {}


int boss::getbossdamage()const
{
	return (this->_bossdamage);
}

void boss::move(float delta)
{
	if (!this->isdead())
	{
		auto moveby1 = MoveBy::create(1.0, Vec2(2 * _moveSpeed, 0));
		auto moveby2 = MoveBy::create(1.0, Vec2(-2 * _moveSpeed, 0));
		auto moveby3 = MoveBy::create(1.0, Vec2(0, 2 * _moveSpeed));
		auto moveby4 = MoveBy::create(1.0, Vec2(0, -2 * _moveSpeed));

		auto winSize = Director::getInstance()->getVisibleSize();
		Vec2 me_size = this->getContentSize();
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
			x += 2 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->getSprite()->setFlippedX(false);
				this->runAction(moveby1);
				this->getSprite()->runAction(boss_Frame_animation());
			}
			break;
		case 2:
			x += 2 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->getSprite()->setFlippedX(true);
				this->runAction(moveby2);
				this->getSprite()->runAction(boss_Frame_animation());
			}
			break;
		case 3:
			y += 2 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby3);
				this->getSprite()->runAction(boss_Frame_animation());
			}
			break;
		case 4:
			y -= 2 * _moveSpeed;
			if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
			{
				this->runAction(moveby4);
				this->getSprite()->runAction(boss_Frame_animation());
			}
			break;
		}
	}
}

void boss::bindAtBattleRoom(battleRoom* curBattleRoom) {
	this->atBattleRoom = curBattleRoom;
}

battleRoom* boss::getAtBattleRoom() const { return this->atBattleRoom; }

void boss::setIsAdded(bool status) { this->isAdded = status; }

bool boss::getIsAdded() const { return this->isAdded; }

bool boss::init() {
	isAdded = false;
	this->settype();
	this->setAttackRange();
	int curtype = this->gettype();
	if (curtype == 0)
	{
		auto bossSP = Sprite::create("Boss1-1.png");
		bindSprite(bossSP);
		this->schedule(CC_SCHEDULE_SELECTOR(boss::move), 1.0f);
		this->schedule(CC_SCHEDULE_SELECTOR(boss::updatedead), 0.01f);
	}
	if (curtype == 1)
	{
		auto bossSP = Sprite::create("Boss2-1.png");
		bindSprite(bossSP);
		this->schedule(CC_SCHEDULE_SELECTOR(boss::move), 1.0f);
		this->schedule(CC_SCHEDULE_SELECTOR(boss::updatedead), 0.01f);
	}
	this->setMaxHP(200);
	this->setHP(200);
	this->setTag(9);
	return true;
}


void boss::setAttackRange() {
	switch (bossType)
	{
	case 0:
		ATTACKRANGE = 400;
		break;
	case 1:
		ATTACKRANGE = 600;
		break;
	}
}


int boss::getAttackRange()const
{
	return ATTACKRANGE;
}


void boss::settype()
{
	int random = rand() % 2;
	bossType = random;
}


int boss::gettype()const
{
	return bossType;
}

Animate* boss::boss_Frame_animation()
{
	auto Boss_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->gettype() == 0)
	{
		for (int i = 1; i < 3; i++)
		{
			sprintf(namesize, "Boss1-%d.png", i);
			Boss_frame_animation->addSpriteFrameWithFile(namesize);
		}
		Boss_frame_animation->setDelayPerUnit(0.2f);
	}

	if (this->gettype() == 1)
	{
		for (int i = 1; i < 8; i++)
		{
			sprintf(namesize, "Boss2-%d.png", i);
			Boss_frame_animation->addSpriteFrameWithFile(namesize);
		}
		Boss_frame_animation->setDelayPerUnit(0.4f);
	}

	Boss_frame_animation->setLoops(1);

	Boss_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(Boss_frame_animation);

	return animate;
}


Animate* boss::boss_Frame_animation_dead()
{
	auto boss_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->gettype() == 0)
	{
		sprintf(namesize, "Boss1-1.png");
		boss_frame_animation->addSpriteFrameWithFile(namesize);
	}
	if (this->gettype() == 1)
	{

		sprintf(namesize, "Boss2-1.png");
		boss_frame_animation->addSpriteFrameWithFile(namesize);
	}

	boss_frame_animation->setDelayPerUnit(0.2f);

	boss_frame_animation->setLoops(-1);

	boss_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(boss_frame_animation);

	return animate;
}
void boss::updatedead(float delta)
{
	if (this->isdead())
	{
		this->getSprite()->runAction(this->boss_Frame_animation_dead());
		this->removeAllComponents();
	}
}