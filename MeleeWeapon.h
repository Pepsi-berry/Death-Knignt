#ifndef _MELEE_WEAPON_
#define _MELEE_WEAPON

#include<weapon.h>

class meleeWeapon :public weapon {
public:
	void setDamage(int damage) { *_damage = damage; }
	int getDamege() { return *_damage; }
	void setMeleeRange(float meleeRange) { *_meleeRange = meleeRange; }
	float getMeleeRange() { return *_meleeRange; }
	void setCDTime(float CDTime) { *_CDTime = CDTime; }
	float getCDTime() { return *_CDTime; }

	static std::shared_ptr<meleeWeapon> createMeleeWeapon(int MPconsume = 0, float attackSpeed = 0, float critRate = 0.0f,
		float critMultiple = 0.0f, float CDTime = 0.1f, float meleeRange = 0, int damage = 1);

	bool initMeleeWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple, float CDTime, float meleeRange, int damage);

	virtual ~meleeWeapon() = default;

	meleeWeapon* clone()const override;

protected:
	std::shared_ptr<int> _damage;
	std::shared_ptr<float> _meleeRange;
	std::shared_ptr<float> _CDTime;

private:
	bool initMeleeWeaponMem(float CDTime, float meleeRange, int damage);
};


#endif // !_MELEE_WEAPON_
