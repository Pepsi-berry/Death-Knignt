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


    /*三个回调函数*/
    void menuCloseCallbackEnd(cocos2d::Ref* pSender);
    void menuCloseCallbackStart(cocos2d::Ref* pSender);
    void menuCloseCallbackSet(cocos2d::Ref* pSender);

    int backgroundAudioID;

    // implement the "static create()" method manually
    CREATE_FUNC(initScene);

private:
    cocos2d::Sprite* mySprite;
};



#endif // !_INIT_SCENE_
