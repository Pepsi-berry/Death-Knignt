#include <bullet.h>
//
inline bool bullet::initMemBullet(float damage, float movingSpeed, bool isCrit)     //完成对主要成员的初始化
{
	auto dmgTemp = std::make_shared<float>(damage);
	if (!dmgTemp) {
		return false;
	}
	else {
		_damage = dmgTemp;
	}
	auto mvspTemp = std::make_shared<float>(movingSpeed);
	if (!mvspTemp) {
		return false;
	}
	else {
		_movingSpeed = mvspTemp;
	}
	_isCrit = isCrit;
	return true;
}
//
bool bullet::initBullet(float damage, float speed, bool crit)                       //
{
	return (Sprite::init() && initMemBullet(damage, speed, crit));
}
//
bullet* bullet::clone(bool isCrit)const {                                           //实现快速复制子弹
	bullet* temp = new(std::nothrow) bullet();

	if (temp) {
		temp->setSpriteFrame(this->getSpriteFrame());
		temp->_damage = _damage;
		temp->_movingSpeed = _movingSpeed;
		temp->_isCrit =isCrit;
		return temp;
	}
	else {
		delete temp;
		temp = nullptr;
		return nullptr;
	}
}
//
//调用以进行一个bullet对象的创建
std::shared_ptr<bullet> bullet::createBullet(float damage, float movingSpeed, bool isCrit)
{
	auto temp = std::make_shared<bullet>();

	if (temp && temp->initBullet(damage, movingSpeed, isCrit)) 
		return temp;
	else 
		return std::shared_ptr<bullet>(nullptr);
}
