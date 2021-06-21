#ifndef _INIT_SCENE_
#define _INIT_SCENE_

#include "cocos2d.h"

USING_NS_CC;
class initScene :public Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    /*回调函数*/
    void menuCloseCallbackEnd(cocos2d::Ref* pSender);
    void menuCloseCallbackStart(cocos2d::Ref* pSender);
    void menuCloseCallbackSet(cocos2d::Ref* pSender);
    void menuCloseCallbackVolumeUp(cocos2d::Ref* pSender);//升高音量
    void menuCloseCallbackVolumeDown(cocos2d::Ref* pSender);//降低音量



    char* G2U(const char* gb2312);      //中文支持
    // implement the "static create()" method manually
    CREATE_FUNC(initScene);

private:
    cocos2d::Sprite* mySprite;
    int BGM;
    cocos2d::Menu* MenuUpVolume;
    cocos2d::Menu* MenuDownVolume;
    /*音量大小标签*/
    cocos2d::Label* volumeNumLab;
    cocos2d::Sprite* backGround;
};



#endif // !_INIT_SCENE_
