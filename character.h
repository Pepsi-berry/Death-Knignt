#ifndef _CHARACTER_
#define _CHARACTER_
#include "cocos2d.h"

USING_NS_CC;

class character :public Node
{
public:
	virtual void move();
	virtual void attack();

	virtual void setHP(int HP) { _hp = (HP > * _hp_max) ? *_hp_max : HP; }
	virtual void setHPMax(int HPMax) { *_hp_max = HPMax; }
	virtual int getHP()const { return _hp; }
	virtual int getHPMax()const { return *_hp_max; }
	
	virtual void setSpeed(float speed) { *_speed = speed; }
	virtual float getSpeed()const { return *_speed; }

	virtual void getdamage(int damage)=0;
	void bindSprite(Sprite* sprite) { _player = sprite; addChild(_player); };
	bool isdead();
protected:
	std::shared_ptr<float> _hp_max;
	std::shared_ptr<float> _speed;
	float _hp;
	float _armor;
	cocos2d::Sprite* _player;
};
#endif