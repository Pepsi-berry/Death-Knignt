#include"character.h"

character::~character() {}

Sprite* character::getSprite() { return base_sprite; }

void character::bindSprite(Sprite* sprite) {
	this->base_sprite = sprite;
	//this->_spriteInCharacter->setGlobalZOrder(layer);

	Size size = this->base_sprite->getContentSize();
	this->setContentSize(size);

	this->setAnchorPoint(Point(0.5f, 0.5f));
	setPosition(Point(.0f, .0f));

	this->addChild(base_sprite);
	this->base_sprite->setPosition(Point(size.width / 2, size.height / 2));
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
	if (this->_HP > damage)
		this->_HP -= damage;
	else
		this->_HP = 0;
}

int character::getHP() const { return this->_HP; }

void character::setHP(int HP) { this->_HP = std::min(HP, _maxHP); }

int character::getMaxHP() const { return this->_maxHP; }

void character::setMaxHP(int maxHP) { this->_maxHP = maxHP; }

float character::getMoveSpeed() const { return _moveSpeed; }

void character::setMoveSpeed(float speed) { this->_moveSpeed = speed; }

bool character::isdead() const { return _HP <= 0; }