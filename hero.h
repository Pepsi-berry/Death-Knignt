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

	void updateWeaponDisplayStatus();

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

	void setMP(int MP) { _MP = MP; }
	int getMP() { return _MP; }
	void setMaxMP(int maxMP) { _maxMP = maxMP; }
	int getMaxMP() { return _maxMP; }
	void setCoin(int coin) { _coin = coin; }
	void addCoin(int deltaCoin);
	int getCoin() { return _coin; }
	void setCurWeaponType(int curWeaponType) { _curWeaponType = curWeaponType; }
	int getCurWeaponType() { return _curWeaponType; }
	void setSecondaryWeaponType(int SecondaryWeaponType) { _secondaryWeaponType = SecondaryWeaponType; }
	int getSecondaryWeaponType() { return _secondaryWeaponType; }

	virtual void getdamage(int damage);

	void pickUpWeapon(weapon* pickedWeapon);

	void changeWeapon();

	void initmem();

	void bindWeapon();
	//void bindSecondaryWeapon(weapon* secondaryWeapon) { _secondaryWeapon = secondaryWeapon; }
	//void bindSecondaryWeapon(weapon* weapon);
	weapon* getCurWeapon();
	int getWeaponType();

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
	weapon* _thirdWeapon;
	weapon* _fourthWeapon;
	weapon* _fifthWeapon;

	int _MP;
	int _maxMP;
	int _armor=0;
	int _armorMax;
	int _coin;
	int _curWeaponType;
	int _secondaryWeaponType;
	bool _isFinished;
	bool _canAttack;
	bool _canChange;
};
#endif