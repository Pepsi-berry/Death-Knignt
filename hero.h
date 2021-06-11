#include "cocos2d.h"
#include "character.h"

USING_NS_CC;

#ifndef _HERO_
#define _HERO_

class hero :public character
{
public:
	hero() = default;
	~hero();
	CREATE_FUNC(hero);

	virtual bool init();

	//绑定场景，用于读取场景里的东西
	void bindscene(Scene* scene);

	void updatekeyboard(float delta);
	void truekeycode(EventKeyboard::KeyCode Keycode);
	void falsekeycode(EventKeyboard::KeyCode Keycode);

	virtual void getdamage(int damage) { _HP -= damage; }
	
protected:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	float _heroSpeed;
	Scene* _scene;
};
#endif