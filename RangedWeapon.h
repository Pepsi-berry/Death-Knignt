#ifndef _RANGED_WEAPON_
#define _RANGED_WEAPON

#include <weapon.h>

class rangedWeapon :public weapon {

public:
	void setCDTime(float CDTime) { *_CDTime = CDTime; }

	float getCDTime() { return *_CDTime; }

	static std::shared_ptr<rangedWeapon> createRangedWeapon(const std::string& spriteFrameName, std::shared_ptr<bullet> Bullet, int MPconsume = 0,
		float attackSpeed = 0, float critRate = 0.0f, float critMultiple = 0.0f, float CDTime = 0.1f);

	bool initRangedWeapon(const std::string& spriteFrameName, std::shared_ptr<bullet> Bullet, int MPconsume,
		float attackSpeed, float critRate, float critMultiple, float CDTime);

	virtual ~rangedWeapon() = default;

	std::shared_ptr<bullet> getBulletInstance()const { return _bullet; };

	rangedWeapon* clone()const override;

protected:
	std::shared_ptr<float> _CDTime;                                                      //射击冷却时间(设定射速)
	std::shared_ptr<bullet> _bullet;
private:
	bool initRangedWeaponMem(std::shared_ptr<bullet> Bullet, float CDTime);
};

#endif // !_RANGED_WEAPON_
