#ifndef _LOSE_SCENE_
#define _LOSE_SCENE_

#include "cocos2d.h"

class loseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallbackEnd(cocos2d::Ref* pSender);//�ر��������Ļص�����
	void menuCloseCallbackChange(cocos2d::Ref* pSender);//�ı����ֲ���״̬�Ļص�����
	char* G2U(const char* gb2312);      //����֧��

	CREATE_FUNC(loseScene);
private:
	//BGM����
	cocos2d::Menu* Menu_On;
	cocos2d::Menu* Menu_Off;
	cocos2d::Sprite* backGround;
};



#endif 

