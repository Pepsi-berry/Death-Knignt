#include "cocos2d.h"
#include "character.h"

#ifndef _HERO_
#define _HERO_
class hero :public character
{
public:
	virtual void move();
	virtual void attack();
	virtual void update(float delta);
	virtual bool init();
	virtual void getdamage(int damage) { _hp -= damage; }
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	void bindscene(Scene* scene);
	CREATE_FUNC(hero);
protected:
	float _hero_speed;
};
#endif
