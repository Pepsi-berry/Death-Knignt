#include "weapon.h"


weapon::~weapon() {}

void weapon::changeWeapon(int changeType)
{
	this->_weaponType = changeType;
	if (_weaponType == 0)
	{
		auto curWeapon = Sprite::create("Weapon//weapon4.png");
		this->weaponInit(300, 3, 400);
		bindSprite(curWeapon);
	}
	if (_weaponType == 1)
	{
		auto curWeapon = Sprite::create("BigKnife1.png");
		this->weaponInit(0, 5, 80);
		bindSprite(curWeapon);
	}

}

Animate* weapon::wea_Frame_animation()
{
	auto sword_frame_animation = Animation::create();

	char namesize[30] = { 0 };

	for (int i = 1; i < 9; i++)
	{
		sprintf(namesize, "BigKnife%d.png", i);
		sword_frame_animation->addSpriteFrameWithFile(namesize);
	}

	sword_frame_animation->setDelayPerUnit(0.01f);

	sword_frame_animation->setLoops(1);

	sword_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(sword_frame_animation);

	return animate;
}


void weapon::setattackRange(float range)
{
	this->_attackRange = range;
}

float weapon::getattackRange()const
{
	return _attackRange;
}

void weapon::bindSprite(Sprite* sprite) 
{
	this->_weaponSprite = sprite;
	//this->_spriteInCharacter->setGlobalZOrder(layer);

	Size size = this->_weaponSprite->getContentSize();
	this->setContentSize(size);

	this->setAnchorPoint(Point(0.5f, 0.5f));
	setPosition(Point(.0f, .0f));

	this->addChild(_weaponSprite);
	this->_weaponSprite->setPosition(Point(size.width / 2, size.height / 2));
}

Sprite* weapon::getSprite() 
{ return _weaponSprite; }

bool weapon::init()
{
	//this->setWeaponType();

	//int curtype = this->getWeaponType();
	//if (curtype == 0)
	//{
	//	auto curWeapon = Sprite::create("Weapon//weapon4.png");
	//	this->weaponInit(300, 3,400);
	//	bindSprite(curWeapon);
	//}
	//if (curtype == 1)
	//{
	//	auto curWeapon = Sprite::create("BigKnife1.png");
	//	this->weaponInit(0, 5,80);
	//	bindSprite(curWeapon);
	//}
	return true;
}

void weapon::setWeaponType()
{
	int random = rand() % 2;
	_weaponType = random;
}

int weapon::getWeaponType()const
{
	return this->_weaponType;
}
void weapon::setFireSpeed(float fireSpeed)
{
	this->_fireSpeed = fireSpeed;
}

float weapon::getFireSpeed()const
{
	return this->_fireSpeed;
}

void weapon::setdamage(int damage)
{
	this->_damage = damage;
}

int weapon::getdamage()const
{
	return this->_damage;
}

void weapon::weaponInit(float speed, int damage,float attackrange)
{
	this->_fireSpeed = speed;
	this->_damage = damage;
	this->_attackRange = attackrange;
}