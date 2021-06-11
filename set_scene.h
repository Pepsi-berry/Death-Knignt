#include "cocos2d.h"
#include"hero.h"
#include"monster.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class set_scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 顺哥这里划重点！！！ 这个函数我不知道是不是你写的 还是系统函数 具体代码在set_scene.cpp里面 你看一下你的文件
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(set_scene);
private:
    monster* monsterfort;
    hero* heroForTest;
    cocos2d::TMXTiledMap* m_tileMap;
    short direction;
};


