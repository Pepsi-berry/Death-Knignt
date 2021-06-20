#ifndef _BULLET_
#define _BULLET_

#include "cocos2d.h"
#include"weapon.h"

USING_NS_CC;


class hero;
class battleScene;

class bullet : public Node {
public:
	bullet() = default;
	~bullet();
	CREATE_FUNC(bullet);

	void bindWeapon(weapon* weapon);
	weapon* getweapon()const;

	int getdamage()const;

	void bindSprite(Sprite* bulletSprite);
	Sprite* getSprite()const;

	void bindHero(hero* curHero);
	hero* getHero()const;

	void bindBattleScene(Scene* curScene);
	Scene* getBattleScene()const;

	void initMem(float speed);

	float getBulletSpeed();

	virtual bool init();

	void fullcreate();

protected:
	int _damage = 3;
	weapon* _curWeapon;
	Sprite* s_bullet;
	hero* t_hero;
	Scene* t_battleScene;
	float _bulletSpeed;
};

#endif