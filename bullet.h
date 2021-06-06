#ifndef _BULLET_
#define _BULLET_

#include "cocos2d.h"
#include <memory>
#include <string>
#include <new>

USING_NS_CC;
//using namespace cocos2d;
//定义抽象子弹类
//用于表示由被操控主角所发出的对怪物造成远程伤害的实体
//具体包括子弹,弓箭,激光等

////后续可能添加子弹的元素效果,如引发debuff及触发率
class bullet :public Sprite {                                                  //此后的大量类基于此格式定义
public:
	//分别设置子弹的伤害,是否暴击和移动速度和是否被使用
	virtual void setDamage(float damage) { *_damage = damage; }
	virtual void setSpeed(float movingSpeed) { *_movingSpeed = movingSpeed; }
	virtual void setCritOrNot(bool isCrit) { _isCrit = isCrit; }
	virtual void setUsedOrNot(bool isUsed) { _isUsed = isUsed; }

	//得到子弹的伤害,移动速度,是否暴击和子弹对象是否使用中
	virtual float getDamage()const { return *_damage; }
	virtual float getSpeed()const { return *_movingSpeed; }
	virtual bool getCritOrNot()const { return _isCrit; }
	virtual float getUsedOrNot()const { return _isUsed; }

	bullet* clone(bool crit)const;

	virtual ~bullet() = default;

	//根据接受的参数创建一个子弹对象并完成初始化
	static std::shared_ptr<bullet> createBullet(const std::string& spriteFrameName, float damage = 0, float movingSpeed = 0.0f,
		bool isCrit = false, bool isUsed = false);

	bool initBullet(const std::string& spriteFrameName, float damage, float speed, bool isCrit, bool isUsed);

	CREATE_FUNC(bullet);
protected:
	std::shared_ptr<float> _movingSpeed;                                  //移速
	std::shared_ptr<float> _damage;                                       //攻击伤害
	bool _isCrit;                                                         //是否暴击
	bool _isUsed;                                                         //是否闲置,以进行管理
private:
	bool initBulletMem(float damage, float movingSpeed, bool isCrit, bool isUsed);
};



#endif