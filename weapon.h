#ifndef _WEAPON_
#define _WEAPON_

#include "cocos2d.h"
#include "bullet.h"
#include <new>
#include <memory>
#include <string>

USING_NS_CC;

class weapon :public cocos2d::Sprite {
public:
	//设置各参数
	virtual void setMPCosume(int mpConsume) { *_MPconsume = mpConsume; }
	virtual void setAspd(float attackSpeed) { *_attackSpeed = attackSpeed; }
	virtual void setCritRate(float critRate) { *_critRate = critRate; }
	virtual void setCritMultiple(float critMultiple) { *_critMultiple = critMultiple; }
	//得到各参数现在值
	virtual int getMPCosume()const { return *_MPconsume; }
	virtual float getAspd()const { return *_attackSpeed; }
	virtual float getCritRate()const { return *_critRate; }
	virtual float getCritMultiple()const { return *_critMultiple; }

	//virtual std::shared_ptr<bullet> getBulletInstance()const = 0;                                //用途不明

	virtual weapon* clone()const = 0;

	bool weapon::initWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple);
protected:
	//bool weapon::initWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple);

	std::shared_ptr<int> _MPconsume;                                      //耗蓝
	std::shared_ptr<float> _attackSpeed;                                  //攻速
	std::shared_ptr<float> _critRate;                                     //暴击率
	std::shared_ptr<float> _critMultiple;                                 //暴击倍数
private:
	//初始化各成员
	bool initWeaponMember(int MPconsume, float attackSpeed, float critRate, float critMultiple);
};




#endif // _WEAPON_
