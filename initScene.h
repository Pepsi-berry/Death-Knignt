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


    /*�ص�����*/
    void menuCloseCallbackEnd(cocos2d::Ref* pSender);
    void menuCloseCallbackStart(cocos2d::Ref* pSender);
    void menuCloseCallbackSet(cocos2d::Ref* pSender);
    void menuCloseCallbackVolumeUp(cocos2d::Ref* pSender);//��������
    void menuCloseCallbackVolumeDown(cocos2d::Ref* pSender);//��������



    char* G2U(const char* gb2312);      //����֧��
    // implement the "static create()" method manually
    CREATE_FUNC(initScene);

private:
    cocos2d::Sprite* mySprite;
    int BGM;
    cocos2d::Menu* MenuUpVolume;
    cocos2d::Menu* MenuDownVolume;
    /*������С��ǩ*/
    cocos2d::Label* volumeNumLab;
    cocos2d::Sprite* backGround;
};



#endif // !_INIT_SCENE_
