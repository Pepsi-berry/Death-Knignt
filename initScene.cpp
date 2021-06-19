#include "initScene.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "secureRoom.h"
#include "settingScene.h"
#include "battleScene.h"
USING_NS_CC;

Scene* initScene::createScene()
{
    return initScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool initScene::init()
{


    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    AudioEngine::stopAll();
    //获取界面尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*背景音乐*/
    backgroundAudioID = AudioEngine::play2d("bkMusic.mp3", false);

    /*开始界面背景图像*/
    auto startBackground = Sprite::create("start.png");
    auto backGroundSize = startBackground->getContentSize();
    //startBackground->setScale(visibleSize.width / backGroundSize.width, visibleSize.height / backGroundSize.height);

    if (startBackground == nullptr)
    {
        problemLoading("'start.png'");
    }
    else {
        startBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        startBackground->setScale(1.10f);
        this->addChild(startBackground, 0);
    }

    /*创建菜单*/
    auto startLab = Label::createWithTTF("START", "fonts/arial.ttf", 24);
    auto exitLab = Label::createWithTTF("EXIT", "fonts/arial.ttf", 24);

    auto startMenu = MenuItemLabel::create(startLab, CC_CALLBACK_1(initScene::menuCloseCallbackStart, this));
    auto exitMenu = MenuItemLabel::create(exitLab, CC_CALLBACK_1(initScene::menuCloseCallbackEnd, this));

    auto setImg = MenuItemImage::create(
        "information.png",
        "information.png",
        CC_CALLBACK_1(initScene::menuCloseCallbackSet, this));
    setImg->setScale(0.2f, 0.2f);
    auto exitImg = MenuItemImage::create(
        "exit.png",
        "exit.png",
        CC_CALLBACK_1(initScene::menuCloseCallbackEnd, this));
    exitImg->setScale(0.4f, 0.4f);
    auto Menu_1 = Menu::create(startMenu, exitMenu, NULL);
    auto Menu_2 = Menu::create(setImg, NULL);
    auto Menu_3 = Menu::create(exitImg, NULL);

    /*垂直排列*/
    Menu_1->alignItemsVertically();

    Menu_1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
    Menu_2->setPosition(visibleSize.width + origin.x - 75, visibleSize.height + origin.y - 25);
    Menu_3->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);

    this->addChild(Menu_1, 1);
    this->addChild(Menu_2, 1);
    this->addChild(Menu_3, 1);


    return true;
}



void initScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

/*退出游戏*/
void initScene::menuCloseCallbackEnd(Ref* pSender)
{
    Director::getInstance()->end();
}

/*开始游戏*/
void initScene::menuCloseCallbackStart(Ref* pSender)
{
    AudioEngine::stop(backgroundAudioID);
    Director::getInstance()->pushScene(initScene::create());
    Director::getInstance()->replaceScene(TransitionSlideInT::create(1.8f, secureRoom::createScene()));
}

/*进入设置面板*/
void initScene::menuCloseCallbackSet(Ref* pSender)
{
    Director::getInstance()->pushScene(TransitionFade::create(2.0f, settingScene::createScene()));
}