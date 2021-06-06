#include <RangedWeapon.h>
//
std::shared_ptr<rangedWeapon> rangedWeapon::createRangedWeapon(const std::string& spriteFrameName, std::shared_ptr<bullet> Bullet, int MPconsume, float attackSpeed,
	float critRate, float critMultiple,float CDTime)
{
	auto temp = std::make_shared<rangedWeapon>();
	if (temp && temp->initRangedWeapon(spriteFrameName, Bullet, MPconsume, attackSpeed, critRate, critMultiple, CDTime))
		return temp;
	else
		return std::shared_ptr<rangedWeapon>(nullptr);
}
//
bool rangedWeapon::initRangedWeapon(const std::string& spriteFrameName, std::shared_ptr<bullet> Bullet, int MPconsume, float attackSpeed,
	float critRate, float critMultiple, float CDTime)
{
	auto spriteTemp = Sprite::create(spriteFrameName);
	auto frameTemp = spriteTemp->getSpriteFrame();
	//return (initWeapon(MPconsume, attackSpeed, critRate, critMultiple) && initRangedWeaponMem(Bullet, CDTime) &&
	//	(this->initWithSpriteFrame(frameTemp)));
	return (Sprite::initWithSpriteFrameName(spriteFrameName)&&initWeapon(MPconsume, attackSpeed, critRate, critMultiple) &&
		initRangedWeaponMem(Bullet, CDTime));
	//return (initWeapon(MPconsume, attackSpeed, critRate, critMultiple) && initRangedWeaponMem(Bullet, CDTime) &&
	//	(this->initWithSpriteFrameName(spriteFrameName)));
}
//
inline bool rangedWeapon::initRangedWeaponMem(std::shared_ptr<bullet> Bullet, float CDTime)
{
	if (!Bullet)
		return false;
	_bullet = Bullet;

	auto CDTimeTemp = std::make_shared<float>(CDTime);
	if (!CDTimeTemp)
		return false;
	_CDTime = CDTimeTemp;
	return true;
}
//
rangedWeapon* rangedWeapon::clone()const 
{
	rangedWeapon* temp = new(std::nothrow) rangedWeapon();

	if (temp) {
		temp->setSpriteFrame(this->getSpriteFrame());
		temp->_MPconsume = _MPconsume;
		temp->_attackSpeed = _attackSpeed;
		temp->_critRate = _critRate;
		temp->_critMultiple = _critMultiple;
		temp->_bullet = _bullet;
		return temp;
	}
	else {
		delete temp;
		temp = nullptr;
		return nullptr;
	}
}
