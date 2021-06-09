#include "character.h"

#ifndef _HERO_
#define _HERO_
USING_NS_CC;

class hero :public character
{
public:
	hero() = default;
	~hero();
	virtual void move();
	virtual void attack();
	virtual void updateKeyboardEvent();
	virtual bool init();
	bool initMemHero(const std::string& fileName, float heroSpeed = 0.0f, int attack = 3, int maxHP = 10, float movingSpeed = 0.0f);
	virtual void getdamage(int damage) { _HP -= damage; }
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	void bindscene(Scene* scene);
	CREATE_FUNC(hero);
protected:
	float _heroSpeed;
};
#endif
