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
//��Ҫ���bullet��ͼʱ�����ڲ���Ա_spriteInBullet���,����Ϊ�������ͳһ��ʽ

////�Ķ����ʼ��˼·�����ı�,����ԭ�г�Ա�����ɵ���InitMemXXXX()���г�ʼ��,�������Sprite*���spriteInXXXX(45�д�����)ר�����ڴ洢�����ͼ,
////��spriteInXXXX�ĳ�ʼ����������Ӵ�����auto spriteInXXXX = Sprite::create("XXXXX.png")��������ʵ��,
////��ԸĶ��������ڱ�cpp�б�ע��,�����ļ��д�������
////������������ӵ���Ԫ��Ч��,������debuff��������
class bullet :public Node {                                                  //�˺�Ĵ�������ڴ˸�ʽ����
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
	/***************************************************�Ķ���***************************************************/
	virtual Sprite* getSpriteInBullet()const { return _spriteInBullet; }     //��Ϊ�ⲿ������ͼspriteInXXXX�Ľӿ�,�������ַ
	/***************************************************�Ķ���***************************************************/

	bullet* clone(bool crit)const;

	virtual ~bullet() = default;

	//���ݽ��ܵĲ�������һ���ӵ�������ɳ�ʼ��
	static std::shared_ptr<bullet> createBullet(const std::string& spriteFrameName, float damage = 0, float movingSpeed = 0.0f,
		bool isCrit = false, bool isUsed = false);

	bool initBullet(const std::string& spriteFrameName, float damage, float speed, bool isCrit, bool isUsed);

	CREATE_FUNC(bullet);
protected:
	/***************************************************�Ķ���***************************************************/
	Sprite* _spriteInBullet;                                              //���þ���洢,��ʼ����ͼ
	/***************************************************�Ķ���***************************************************/
	std::shared_ptr<float> _movingSpeed;                                  //����
	std::shared_ptr<float> _damage;                                       //�����˺�
	bool _isCrit;                                                         //�Ƿ񱩻�
	bool _isUsed;                                                         //�Ƿ�����,�Խ��й���
private:
	bool initBulletMem(float damage, float movingSpeed, bool isCrit, bool isUsed);
};



#endif