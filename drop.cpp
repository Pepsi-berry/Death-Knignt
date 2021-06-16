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
		bindSprite(curdrop);
	}
	if (curtype == 1)
	{
		auto curdrop = Sprite::create("Props//add_HP.png");
		bindSprite(curdrop);
	}
	if (curtype == 2)
	{
		auto curdrop = Sprite::create("Props//add_MP.png");
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