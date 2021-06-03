#ifndef _BULLET_
#define _BULLET_

#include "cocos2d.h"
#include <memory>
#include <string>
#include <new>

USING_NS_CC;
//using namespace cocos2d;
//��������ӵ���
//���ڱ�ʾ�ɱ��ٿ������������ĶԹ������Զ���˺���ʵ��
//��������ӵ�,����,�����

////������������ӵ���Ԫ��Ч��,������debuff��������
class bullet :public Sprite {                                                  //�˺�Ĵ�������ڴ˸�ʽ����
public:
	//�ֱ������ӵ����˺�,�Ƿ񱩻����ƶ��ٶȺ��Ƿ�ʹ��
	virtual void setDamage(float damage) { *_damage = damage; }
	virtual void setSpeed(float movingSpeed) { *_movingSpeed = movingSpeed; }
	virtual void setCritOrNot(bool isCrit) { _isCrit = isCrit; }
	virtual void setUsedOrNot(bool isUsed) { _isUsed = isUsed; }

	//�õ��ӵ����˺�,�ƶ��ٶ�,�Ƿ񱩻����ӵ������Ƿ�ʹ����
	virtual float getDamage()const { return *_damage; }
	virtual float getSpeed()const { return *_movingSpeed; }
	virtual bool getCritOrNot()const { return _isCrit; }
	virtual float getUsedOrNot()const { return _isUsed; }

	bool initBullet(float damage, float speed, bool crit);

	bullet* clone(bool crit)const;

	virtual ~bullet() = default;

	//���ݽ��ܵĲ�������һ���ӵ�������ɳ�ʼ��
	static std::shared_ptr<bullet> createBullet(float damage = 0, float movingSpeed = 0.0f, bool isCrit = false);
protected:
	std::shared_ptr<float> _movingSpeed;                                  //����
	std::shared_ptr<float> _damage;                                       //�����˺�
	bool _isCrit;                                                         //�Ƿ񱩻�
	bool _isUsed;                                                         //�Ƿ�����,�Խ��й���
private:
	bool initMemBullet(float damage, float movingSpeed, bool isCrit);
};



#endif