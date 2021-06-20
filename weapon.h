#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "cocos2d.h"

USING_NS_CC;

class weapon : public Node {
public:
	weapon() = default;
	~weapon();
	CREATE_FUNC(weapon);

	void changeWeapon(int changeType);

	void bindSprite(Sprite* sprite);
	Sprite* getSprite();

	void setWeaponType();

	int getWeaponType()const;

	virtual bool init();

	void setFireSpeed(float fireSpeed);

	float getFireSpeed()const;

	void setdamage(int damage);

	int getdamage()const;

	void setattackRange(float range);
	float getattackRange()const;

	void setMPCost(int MPCost) { _MPCost = MPCost; }
	int getMPCost() { return _MPCost; }

	void setWeaponPrice(int weaponPrice) { _weaponPrice = weaponPrice; }
	int getWeaponPrice() { return _weaponPrice; }

	void weaponInit(float speed, int damage, float attackrange, int MPCost);

	Animate* wea_Frame_animation();
protected:
	Sprite* _weaponSprite;
	int _weaponType;
	int _MPCost;
	float _fireSpeed;
	int _damage;
	float _attackRange;
	int _weaponPrice;
};
#endif;
