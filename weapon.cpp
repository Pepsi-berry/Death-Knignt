#include "weapon.h"


weapon::~weapon() {}

void weapon::changeWeapon(int changeType)
{
	this->_weaponType = changeType;
	if (_weaponType == 0)
	{
		//单发步枪
		auto curWeapon = Sprite::create("Weapon//weapon0.png");
		this->weaponInit(300, 3, 400, 3);
		_weaponPrice = 30 + rand() % 15;
		bindSprite(curWeapon);
	}
	if (_weaponType == 1)
	{
		//大剑
		auto curWeapon = Sprite::create("BigKnife1.png");
		this->weaponInit(0, 3, 120, 0);
		_weaponPrice = 40 + rand() % 12;
		bindSprite(curWeapon);
	}
	if (_weaponType == 2)
	{
		//冲锋枪  目前点射 请按之前自己思路修改
		auto curWeapon = Sprite::create("Weapon//weapon2.png");
		this->weaponInit(400, 2, 300, 1);
		_weaponPrice = 25 + rand() % 20;
		bindSprite(curWeapon);
	}
	if (_weaponType == 3)
	{
		//范围伤法杖
		auto curWeapon = Sprite::create("Weapon//weapon_4.png");
		this->weaponInit(0, 2, 400, 5);
		_weaponPrice = 50 + rand() % 20;
		bindSprite(curWeapon);
	}
	if (_weaponType == 4)
	{
		//近战黄金锤
		auto curWeapon = Sprite::create("Weapon//BigKnife2-1.png");
		this->weaponInit(0, 4, 160, 0);
		_weaponPrice = 35 + rand() % 20;
		bindSprite(curWeapon);
	}
}

Animate* weapon::wea_Frame_animation()
{
	auto sword_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (_weaponType == 1)
	{
		for (int i = 1; i < 9; i++)
		{
			sprintf(namesize, "BigKnife%d.png", i);
			sword_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}
	if (_weaponType == 4)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Weapon//BigKnife2-%d.png", i);
			sword_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	sword_frame_animation->setDelayPerUnit(0.05f);

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
	if(_weaponType == 1 || _weaponType == 3|| _weaponType == 4)
		this->_weaponSprite->setPosition(Point(size.width / 2, size.height / 2));
	if (_weaponType == 0 || _weaponType == 2)
		this->_weaponSprite->setPosition(Point(size.width / 2, size.height / 4));
}

Sprite* weapon::getSprite() 
{ return _weaponSprite; }

bool weapon::init()
{
	return true;
}

void weapon::setWeaponType()
{
	int random = rand() % 5;
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

void weapon::weaponInit(float speed, int damage,float attackrange,int MPCost)
{
	this->_fireSpeed = speed;
	this->_damage = damage;
	this->_attackRange = attackrange;
	this->_MPCost = MPCost;
}