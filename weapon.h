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
	//���ø�����
	virtual void setMPCosume(int mpConsume) { *_MPconsume = mpConsume; }
	virtual void setAspd(float attackSpeed) { *_attackSpeed = attackSpeed; }
	virtual void setCritRate(float critRate) { *_critRate = critRate; }
	virtual void setCritMultiple(float critMultiple) { *_critMultiple = critMultiple; }
	//�õ�����������ֵ
	virtual int getMPCosume()const { return *_MPconsume; }
	virtual float getAspd()const { return *_attackSpeed; }
	virtual float getCritRate()const { return *_critRate; }
	virtual float getCritMultiple()const { return *_critMultiple; }

	//virtual std::shared_ptr<bullet> getBulletInstance()const = 0;                                //��;����

	virtual weapon* clone()const = 0;

	bool weapon::initWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple);
protected:
	//bool weapon::initWeapon(int MPconsume, float attackSpeed, float critRate, float critMultiple);

	std::shared_ptr<int> _MPconsume;                                      //����
	std::shared_ptr<float> _attackSpeed;                                  //����
	std::shared_ptr<float> _critRate;                                     //������
	std::shared_ptr<float> _critMultiple;                                 //��������
private:
	//��ʼ������Ա
	bool initWeaponMember(int MPconsume, float attackSpeed, float critRate, float critMultiple);
};




#endif // _WEAPON_
