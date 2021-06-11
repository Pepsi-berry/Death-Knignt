#ifndef _CHARACTER_
#define _CHARACTER_

#include "cocos2d.h"

USING_NS_CC;

class character :public Node {
public:
	character() = default;

	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

	virtual void showDeathEffect();
	virtual void getdamage(int damage);

	void setMaxHP(int maxhp);
	int getMaxHP() const;
	void setHP(int hp);
	int getHP() const;
	void setMoveSpeed(float movespeed);
	float getMoveSpeed() const;

	bool isdead() const;

	~character();

protected:
	Sprite* base_sprite;
	int _HP = 10, _maxHP = 10;
	float _moveSpeed = 0.0f;

};

#endif //_CHARACTER_