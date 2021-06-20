#include"drop.h"

drop::~drop() {}

void drop::bindSprite(Sprite* sprite) {
	this->_dropsprite = sprite;
	//this->_spriteInCharacter->setGlobalZOrder(layer);

	Size size = this->_dropsprite->getContentSize();
	this->setContentSize(size);

	this->setAnchorPoint(Point(0.5f, 0.5f));
	setPosition(Point(.0f, .0f));

	this->addChild(_dropsprite);
	this->_dropsprite->setPosition(Point(size.width / 2, size.height / 2));
}

bool drop::init() 
{
	_isUsed = 0;
	this->settype();
	//PhysicsBody* dropbody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	//dropbody->setGravityEnable(false);
	//dropbody->setDynamic(false);
	//dropbody->setCategoryBitmask(0x0001);
	//dropbody->setCollisionBitmask(0x0001);
	//dropbody->setContactTestBitmask(0x0001);
	//this->addComponent(dropbody);
	//this->setTag(5);
	int curtype = this->gettype();
	if (curtype == 0)
	{
		auto curdrop = Sprite::create("Props//add_gold.png");
		_dropPrice = 0;
		bindSprite(curdrop);
	}
	if (curtype == 1)
	{
		auto curdrop = Sprite::create("Props//add_HP.png");
		_dropPrice = 20 + rand() % 10;
		bindSprite(curdrop);
	}
	if (curtype == 2)
	{
		auto curdrop = Sprite::create("Props//add_MP.png");
		_dropPrice = 15 + rand() % 7;
		bindSprite(curdrop);
	}
	return true;
}

void drop::settype()
{
	int random = rand() % 3;
	_dropType = random;
}

int drop::gettype()const
{
	return _dropType;
}

void drop::propsUsing(hero* Hero)
{
	if (_dropType == 0)
		Hero->addCoin(10);
	else if (_dropType == 1)
		Hero->getdamage(-2);
	else if (_dropType == 2)
	{
		auto curMP = Hero->getMP();
		auto curMaxMP = Hero->getMaxMP();
		if (curMP + 80 <= curMaxMP)
			Hero->setMP(curMP + 80);
		else
			Hero->setMP(curMaxMP);
	}
}