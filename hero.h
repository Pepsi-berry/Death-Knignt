#include "cocos2d.h"
#include "character.h"

USING_NS_CC;

#ifndef _HERO_
#define _HERO_

class monster;

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

	void setMaxArmor(int maxarmor);
	int getMaxArmor() const;
	void setArmor(int armor);
	int getArmor() const;

	void setmovespeedX(float spd);
	void setmovespeedY(float spd);
	float getmovespeedX() const;
	float getmovespeedY() const;

	virtual void getdamage(int damage);

	void initmem(float speed, int armormax, int hpmax);

	Animate* Frame_animation();
	
protected:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	float _heroSpeedX = 5, _heroSpeedY = 5;
	Scene* _scene;
	int _armor;
	int _armorMax;
};
#endif