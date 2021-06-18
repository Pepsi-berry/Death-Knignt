#include "cocos2d.h"
#include "character.h"
#include "bullet.h"
#include "weapon.h"

USING_NS_CC;

#ifndef _HERO_
#define _HERO_

class monster;
class battleRoom;
class room;

class hero :public character
{
public:
	hero() = default;
	~hero();
	CREATE_FUNC(hero);

	virtual bool init();

	void setHeroType(int type);
	int getHeroType()const;

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

	void setCurBattleRoom(battleRoom* curBattleRoom) { _curBattleRoom = curBattleRoom; }
	battleRoom* getCurBattleRoom() { return _curBattleRoom; }

	void setCurCorridor(room* curCorridor) { _curCorridor = curCorridor; }
	room* getCurCorridor() { return _curCorridor; }

	void setIsFinished(bool isFinished) { _isFinished = isFinished; }
	bool getIsFinished() { return _isFinished; }

	virtual void getdamage(int damage);

	void initmem();

	void bindWeapon(weapon* weapon);
	weapon* getCurWeapon();
	weapon* getSecondaryWeapon();
	int getWeaponType()const;

	Animate* Frame_animation_rest();
	Animate* Frame_animation_attack();
	
protected:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	int _heroType;
	float _heroSpeedX = 5, _heroSpeedY = 5;
	Scene* _scene;

	//储存英雄所处的房间或走廊,便于进行边界判定,元素生成等操作
	battleRoom* _curBattleRoom;
	room* _curCorridor;
	weapon* _curWeapon;
	weapon* _secondaryWeapon;

	int _armor=0;
	int _armorMax;
	bool _isFinished;
	bool _canAttack;
};
#endif