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
	if (!this->isdead())
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
			if (this->gettype() == 0|| this->gettype() == 2)
			{
				x += 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->getSprite()->setFlippedX(false);
					this->runAction(moveby1);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			if (this->gettype() == 1|| this->gettype() == 3)
			{
				x += 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->getSprite()->setFlippedX(false);
					this->runAction(moveby5);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			break;
		case 2:
			if (this->gettype() == 0 || this->gettype() == 2)
			{
				x -= 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->getSprite()->setFlippedX(true);
					this->runAction(moveby2);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			if (this->gettype() == 1 || this->gettype() == 3)
			{
				x -= 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->getSprite()->setFlippedX(true);
					this->runAction(moveby6);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			break;
		case 3:
			if (this->gettype() == 0 || this->gettype() == 2)
			{
				y += 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby3);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			if (this->gettype() == 1 || this->gettype() == 3)
			{
				y += 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby7);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			break;
		case 4:
			if (this->gettype() == 0 || this->gettype() == 2)
			{
				y -= 5 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby4);
					this->getSprite()->runAction(mons_Frame_animation_rest());
				}
			}
			if (this->gettype() == 1 || this->gettype() == 3)
			{
				y -= 3 * _moveSpeed;
				if (x > Xmin && x < Xmax && y>Ymin && y < Ymax)
				{
					this->runAction(moveby8);
					this->getSprite()->runAction(mons_Frame_animation_rest());
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
	if (curtype == 0)//Öí
	{
		auto monsterSP = Sprite::create("Monster//pig_monster_rest1.png");
		bindSprite(monsterSP);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::updatedead), 0.01f);
	}
	if (curtype == 1)//¹­¼ýÊÖ	
	{
		auto monsterSP = Sprite::create("Monster1//O_small_monster_rest1.png");
		bindSprite(monsterSP);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::updatedead), 0.01f);
	}
	if (curtype == 2)//»Æ½ðÖí
	{
		auto monsterSP = Sprite::create("Monster1//Y_craw_monster_rest1.png");
		bindSprite(monsterSP);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::updatedead), 0.01f);
	}
	if (curtype == 3)//Ñ©ÇòÉäÊÖ
	{
		auto monsterSP = Sprite::create("Monster1//snow_monster_rest1.png");
		bindSprite(monsterSP);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::move), 1.0f);
		this->schedule(CC_SCHEDULE_SELECTOR(monster::updatedead), 0.01f);
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
	case 2:
		ATTACKRANGE = 300;
		break;
	case 3:
		ATTACKRANGE = 500;
		break;
	}
}

int monster::getAttackRange()const
{
	return ATTACKRANGE;
}

void monster::settype()
{
	int random = rand() % 4;
	enemyType = random;
}

int monster::gettype()const
{
	return enemyType;
}

Animate* monster::mons_Frame_animation()
{
	auto monster_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->gettype() == 0)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster//pig_monster_move%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	if (this->gettype() == 1)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster1//O_small_monster_move%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	if (this->gettype() == 2)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster1//Y_craw_monster_move%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	if (this->gettype() == 3)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster1//snow_monster_move%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	monster_frame_animation->setDelayPerUnit(0.2f);

	monster_frame_animation->setLoops(1);

	monster_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(monster_frame_animation);

	return animate;
}

Animate* monster::mons_Frame_animation_rest()
{
	auto monster_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->gettype() == 0)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster//pig_monster_rest%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}
	if (this->gettype() == 1)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster1//O_small_monster_rest%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	if (this->gettype() == 2)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster1//Y_craw_monster_rest%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	if (this->gettype() == 3)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Monster1//snow_monster_rest%d.png", i);
			monster_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	monster_frame_animation->setDelayPerUnit(0.2f);

	monster_frame_animation->setLoops(1);

	monster_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(monster_frame_animation);

	return animate;
}

Animate* monster::mons_Frame_animation_dead()
{
	auto monster_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->gettype() == 0)
	{
		sprintf(namesize, "Monster//pig_monster_dead.png");
		monster_frame_animation->addSpriteFrameWithFile(namesize);
	}
	if (this->gettype() == 1)
	{

		sprintf(namesize, "Monster1//O_small_monster_dead.png");
		monster_frame_animation->addSpriteFrameWithFile(namesize);
	}

	if (this->gettype() == 2)
	{

		sprintf(namesize, "Monster1//Y_craw_monster_dead.png");
		monster_frame_animation->addSpriteFrameWithFile(namesize);
	}

	if (this->gettype() == 3)
	{

		sprintf(namesize, "Monster1//snow_monster_dead.png");
		monster_frame_animation->addSpriteFrameWithFile(namesize);
	}

	monster_frame_animation->setDelayPerUnit(0.2f);

	monster_frame_animation->setLoops(-1);

	monster_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(monster_frame_animation);

	return animate;
}
void monster::updatedead(float delta)
{
	if (this->isdead())
	{
		this->getSprite()->runAction(this->mons_Frame_animation_dead());
		this->removeAllComponents();
	}
}