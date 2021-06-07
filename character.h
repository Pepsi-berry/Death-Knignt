#ifndef _CHARACTER_
#define _CHARACTER_

#include "cocos2d.h"

USING_NS_CC;

class character :public Node {
public:
	character() = default;

	Sprite* getSprite();

	void bindSprite(Sprite* sprite, int layer);

	virtual void showDeathEffect();

	void setMaxHP(int maxhp);
	int getMaxHP() const;
	void setHP(int hp);
	int getHP() const;
	void setMoveSpeed(float movespeed);
	float getMoveSpeed() const;

	virtual void getdamage(int damage);

	bool isdead() const;

	~character();

private:
	Sprite* sprite;
protected:
	int attack = 3;
	int HP = 10, maxHP = 10;
	//float attackSpeed = 0.0f;  
	float moveSpeed = 0.0f;  

};

#endif //_CHARACTER_