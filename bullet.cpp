#include <bullet.h>
//
inline bool bullet::initBulletMem(float damage, float movingSpeed, bool isCrit, bool isUsed)     //��ɶ���Ҫ��Ա�ĳ�ʼ��
{
	auto dmgTemp = std::make_shared<float>(damage);
	if (!dmgTemp) 
		return false;
	else 
		_damage = dmgTemp;

	auto mvspTemp = std::make_shared<float>(movingSpeed);
	if (!mvspTemp) 
		return false;
	else 
		_movingSpeed = mvspTemp;
	_isCrit = isCrit;
	_isUsed = isUsed;
	return true;
}
//
bool bullet::initBullet(const std::string& spriteFrameName, float damage, float speed, bool isCrit, bool isUsed)
{
	/***************************************************�Ķ���***************************************************/
	return ((_spriteInBullet = Sprite::create(spriteFrameName)) && initBulletMem(damage, speed, isCrit, isUsed));
	/***************************************************�Ķ���***************************************************/
}
//
bullet* bullet::clone(bool isCrit)const {                                           //ʵ�ֿ��ٸ����ӵ�
	bullet* temp = new(std::nothrow) bullet();

	if (temp)
	{
		/***************************************************�Ķ���***************************************************/
		temp->_spriteInBullet->setSpriteFrame(this->_spriteInBullet->getSpriteFrame());
		/***************************************************�Ķ���***************************************************/
		temp->_damage = _damage;
		temp->_movingSpeed = _movingSpeed;
		temp->_isCrit =isCrit;
		return temp;
	}
	else
	{
		delete temp;
		temp = nullptr;
		return nullptr;
	}
}
//
//�����Խ���һ��bullet����Ĵ���
std::shared_ptr<bullet> bullet::createBullet(const std::string& spriteFrameName, float damage, float movingSpeed, bool isCrit, bool isUsed)
{
	auto temp = std::make_shared<bullet>();
	  
	if (temp && temp->initBullet(spriteFrameName, damage, movingSpeed, isCrit, isUsed))
		return temp;
	else 
		return std::shared_ptr<bullet>(nullptr);
}
