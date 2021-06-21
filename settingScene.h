#ifndef _SETTING_SCENE_
#define _SETTING_SCENE

#include "cocos2d.h"

class settingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallbackEnd(cocos2d::Ref* pSender);//关闭设置面板的回调函数
	void menuCloseCallbackChange(cocos2d::Ref* pSender);//改变音乐播放状态的回调函数
	char* G2U(const char* gb2312);      //中文支持

	CREATE_FUNC(settingScene);
private:
	//BGM开关
	cocos2d::Menu* Menu_On;
	cocos2d::Menu* Menu_Off;
	cocos2d::Sprite* backGround;
	int volume;
	int audio;
};



#endif // !_SETTING_SCENE_
