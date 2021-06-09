#include "cocos2d.h"
#include "hero.h"
#include "HelloWorldScene.h"
#include "globalVariable.h"


USING_NS_CC;

class set_scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float delta);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

    // implement the "static create()" method manually
    CREATE_FUNC(set_scene);
private:
    hero* heroForTest;
    cocos2d::TMXTiledMap* m_tileMap;
    short direction;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;

};


