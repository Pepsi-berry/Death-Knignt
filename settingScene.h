#ifndef _SETTING_SCENE_
#define _SETTING_SCENE

#include "cocos2d.h"

class settingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallbackEnd(cocos2d::Ref* pSender);//�ر��������Ļص�����
	void menuCloseCallbackChange(cocos2d::Ref* pSender);//�ı����ֲ���״̬�Ļص�����


	CREATE_FUNC(settingScene);
private:
	//�˵�
	cocos2d::Menu* Menu01;
	cocos2d::Menu* Menu02;
	cocos2d::Menu* Menu03;

};



#endif // !_SETTING_SCENE_
