#include <bullet.h>

bullet::~bullet() {}

int bullet::getdamage()const
{
	return this->_damage;
}

void bullet::bindSprite(Sprite* bulletSprite)
{
	this->s_bullet = bulletSprite;
	Size size = this->s_bullet->getContentSize();
	this->setContentSize(size);

	this->setAnchorPoint(Point(0.5f, 0.5f));
	setPosition(Point(.0f, .0f));

	this->addChild(s_bullet);
	this->s_bullet ->setPosition(Point(size.width / 2, size.height / 2));
}

Sprite* bullet::getSprite()const
{
	return this->s_bullet;
}

void bullet::bindHero(hero* curHero)
{
	this->t_hero = curHero;
}

hero* bullet::getHero()const
{
	return this->t_hero;
}

void bullet::bindBattleScene(Scene* curbattleScene)
{
	this->t_battleScene = curbattleScene;
}

Scene* bullet::getBattleScene()const
{
	return this->t_battleScene;
}

void bullet::initMem(float speed)
{
	this->_bulletSpeed = speed;
}

float bullet::getBulletSpeed()
{
	return this->_bulletSpeed;
}

bool bullet::init()
{
	auto t_bullet = Sprite::create("Bullet//bigBullet.png");
	bindSprite(t_bullet);
	return true;
}