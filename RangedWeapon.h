#ifndef _RANGED_WEAPON_
#define _RANGED_WEAPON

#include <weapon.h>

class rangedWeapon :public weapon {

public:
	static std::shared_ptr<rangedWeapon> createRangedWeapon(int MPconsume = 0, float attackSpeed = 0, float critRate = 0.0f,
		float critMultiple = 0.0f, std::shared_ptr<bullet> bullet = bullet::createBullet());
	bool initRangedWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple, std::shared_ptr<bullet> Bullet);

	virtual ~rangedWeapon() = default;

	std::shared_ptr<bullet> getBulletInstance()const { return _bullet; };

	rangedWeapon* clone()const override;

protected:
	int _CDShoot;                                                         //射击冷却时间(设定射速)
	std::shared_ptr<bullet> _bullet;
private:
	bool initRangedWeaponMem(std::shared_ptr<bullet> Bullet);
};

#endif // !_RANGED_WEAPON_
