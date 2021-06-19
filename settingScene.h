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


	CREATE_FUNC(settingScene);
private:
	//菜单
	cocos2d::Menu* Menu01;
	cocos2d::Menu* Menu02;
	cocos2d::Menu* Menu03;

};



#endif // !_SETTING_SCENE_
