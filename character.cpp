#include"character.h"

USING_NS_CC;

character::~character() {}

Sprite* character::getSprite() { return this->sprite; }

void character::bindSprite(Sprite* sprite, int layer) {
	this->sprite = sprite;
	this->sprite->setGlobalZOrder(layer);

	Size size = this->sprite->getContentSize();
	this->setContentSize(size); 

	this->setAnchorPoint(Point(0.5f, 0.5f)); 
	setPosition(Point(.0f, .0f));

	this->addChild(sprite);
	sprite->setPosition(Point(size.width / 2, size.height / 2));
}

void character::showDeathEffect() {
	auto blink = Blink::create(0.5f, 3);
	auto FadeOut = FadeOut::create(0.5f);
	auto callFunc = CallFunc::create([&]() {
		this->retain();
		this->removeFromParent();
		});

	auto sequence = Sequence::create(Spawn::create(blink, FadeOut, NULL), callFunc, NULL);
	this->getSprite()->runAction(sequence);
}

void character::getdamage(int damage) { 
	if (getSprite() == nullptr) return;
	if (this->HP > damage)
		this->HP -= damage;
	else
		this->HP = 0;

	/*受伤特效*/
	/*FlowWord* flowWord = FlowWord::create();
	this->addChild(flowWord);
	flowWord->showWord(-delta,
		getSprite()->getPosition() +
		Vec2(0, this->getContentSize().height / 2.2f));*/
}

int character::getHP() const { return this->HP; }

void character::setHP(int HP) { this->HP = std::min(HP, maxHP); }

int character::getMaxHP() const { return this->maxHP; }

void character::setMaxHP(int maxHP) { this->maxHP = maxHP; }

float character::getMoveSpeed() const { return moveSpeed; }

void character::setMoveSpeed(float speed) { this->moveSpeed = speed; }

bool character::isdead() const { return HP<=0; }
