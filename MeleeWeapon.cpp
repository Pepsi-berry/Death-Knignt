#include<MeleeWeapon.h>

//
std::shared_ptr<meleeWeapon> meleeWeapon::createMeleeWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple,
	float CDTime, float meleeRange, int damage)
{
	auto temp = std::make_shared<meleeWeapon>();
	if (temp && temp->initMeleeWeapon(MPconsume, attackSpeed, critRate, critMultiple, CDTime, meleeRange, damage))
		return temp;
	else
		return std::shared_ptr<meleeWeapon>(nullptr);
}
//
bool meleeWeapon::initMeleeWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple, float CDTime, float meleeRange, int damage)
{
	return (initWeapon(MPconsume, attackSpeed, critRate, critMultiple) && initMeleeWeaponMem(CDTime, meleeRange, damage));
}
//
bool meleeWeapon::initMeleeWeaponMem(float CDTime, float meleeRange, int damage)
{
	auto CDTimeTemp = std::make_shared<float>(CDTime);
	if (!CDTimeTemp)
		return false;
	else
		_CDTime = CDTimeTemp;

	auto meleeRangeTemp = std::make_shared<float>(meleeRange);
	if (!meleeRange)
		return false;
	else
		_meleeRange = meleeRangeTemp;

	auto damageTemp = std::make_shared<int>(damage);
	if (!damageTemp)
		return false;
	else
		_damage = damageTemp;

	return true;
}
//
meleeWeapon* meleeWeapon::clone()const
{
	meleeWeapon* temp = new(std::nothrow) meleeWeapon();

	if (temp) {
		temp->spriteInMeleeWeapon->setSpriteFrame(this->spriteInMeleeWeapon->getSpriteFrame());
		temp->_MPconsume = _MPconsume;
		temp->_attackSpeed = _attackSpeed;
		temp->_critRate = _critRate;
		temp->_critMultiple = _critMultiple;
		temp->_CDTime = _CDTime;
		temp->_meleeRange = _meleeRange;
		temp->_damage = _damage;
		return temp;
	}
	else {
		delete temp;
		temp = nullptr;
		return nullptr;
	}
}
