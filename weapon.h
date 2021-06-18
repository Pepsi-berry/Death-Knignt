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

	void weaponInit(float speed, int damage,float attackrange);

	Animate* wea_Frame_animation();
protected:
	Sprite* _weaponSprite;
	int _weaponType;
	float _fireSpeed;
	int _damage;
	float _attackRange;
};
#endif;
