#ifndef _SETTING_SCENE_
#define _SETTING_SCENE

#include "cocos2d.h"

class settingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallbackEnd(cocos2d::Ref* pSender);//�ر��������Ļص�����

	CREATE_FUNC(settingScene);
private:



};



#endif // !_SETTING_SCENE_
