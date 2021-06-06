#include "weapon.h"

inline bool weapon::initWeaponMember(
	int MPconsume, float attackSpeed, float critRate, float critMultiple)           //串联结构逐个初始化各成员,保证全部成功时返回true
{
	auto MPconsumeTemp = std::make_shared<int>(MPconsume);
	if (!MPconsumeTemp) 
		return false;
	else 
		_MPconsume = MPconsumeTemp;

	auto attackSpeedTemp = std::make_shared<float>(attackSpeed);
	if (!MPconsumeTemp)
		return false;
	else 
		_attackSpeed = attackSpeedTemp;

	auto critRateTemp = std::make_shared<float>(critRate);
	if (!critRateTemp) 
		return false;
	else 
		_critRate = critRateTemp;

	auto critMultipleTemp = std::make_shared<float>(critMultiple);
	if (!critMultipleTemp) 
		return false;
	else 
		_critMultiple = critMultipleTemp;

	return true;
}

bool weapon::initWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple)
{
	return (Sprite::init() && initWeaponMember(MPconsume, attackSpeed, critRate, critMultiple));
}