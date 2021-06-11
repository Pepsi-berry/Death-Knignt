#include"cocos2d.h"
#include"set_scene.h"



USING_NS_CC;

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


Scene* set_scene::createScene()
{
    return set_scene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool set_scene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto winSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // set Background with grey colour
    auto background = DrawNode::create();
    background->drawSolidRect(origin, winSize, cocos2d::Color4F(0.6f, 0.6f, 0.6f, 1.0f));
    this->addChild(background);

    m_tileMap = TMXTiledMap::create("mymap.tmx");
    m_tileMap->setPosition(winSize.width * 0, winSize.height * 0);
    this->addChild(m_tileMap);

    heroForTest = hero::create();
    heroForTest->bindscene(this);
    heroForTest->getSprite()->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
    this->addChild(heroForTest, 5);


    int winx = winSize.width;
    int winy = winSize.height;
    monsterfort = monster::create();
    monsterfort->bindAtBattleRoom(this);
    monsterfort->getSprite()->setPosition(std::rand() % ((int)(0.75*winx))+ (int)(0.25 * winx), std::rand() % ((int)(0.75 * winy)) + (int)(0.25 * winy));
    this->addChild(monsterfort, 5);

    return true;
}


//void set_scene::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//
//
//}





