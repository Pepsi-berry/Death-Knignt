#include <RangedWeapon.h>
//
std::shared_ptr<rangedWeapon> rangedWeapon::createRangedWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple, std::shared_ptr<bullet> Bullet)
{
	auto temp = std::make_shared<rangedWeapon>();
	if (temp && temp->initRangedWeapon(MPconsume, attackSpeed, critRate, critMultiple, Bullet))
		return temp;
	else 
		return std::shared_ptr<rangedWeapon>(nullptr);
}
//
bool rangedWeapon::initRangedWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple, std::shared_ptr<bullet> Bullet)
{
	return (initWeapon(MPconsume, attackSpeed, critRate, critMultiple) && initRangedWeaponMem(Bullet));
}
//
bool rangedWeapon::initRangedWeaponMem(std::shared_ptr<bullet> Bullet)
{
	if (!Bullet)
		return false;
	_bullet = Bullet;
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
