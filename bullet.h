#ifndef _BULLET_
#define _BULLET_

#include "cocos2d.h"

USING_NS_CC;

class hero;
class battleScene;

class bullet : public Node {
public:
	bullet() = default;
	~bullet();
	CREATE_FUNC(bullet);

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

protected:
	int _damage = 3;
	Sprite* s_bullet;
	hero* t_hero;
	Scene* t_battleScene;
	float _bulletSpeed;
};

#endif