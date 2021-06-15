#ifndef _CHARACTER_
#define _CHARACTER_

#include "cocos2d.h"
//class battleRoom;

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
	//void bindCurBattleRoom(battleRoom* curBattleRoom) { _curBattelRoom = curBattleRoom; }

	bool isdead() const;

	~character();

protected:
	Sprite* base_sprite;
	//battleRoom* _curBattelRoom;
	int _HP = 10, _maxHP = 10;
	float _moveSpeed = 12.0f;

};

#endif //_CHARACTER_