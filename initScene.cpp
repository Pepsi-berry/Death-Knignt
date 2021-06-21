#include "initScene.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "secureRoom.h"
#include "settingScene.h"
#include "battleScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* initScene::createScene()
{
    return initScene::create();
}

//转换中文
char* initScene::G2U(const char* gb2312)
{
    int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr) delete[] wstr;
    return str;
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
    AudioEngine::uncacheAll();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backGround = Sprite::create("start.png");
    auto backGroundSize = backGround->getContentSize();
    backGround->setScale(visibleSize.width / backGroundSize.width, visibleSize.height / backGroundSize.height);

    backGround->setPosition(
        Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backGround, 0);

    /*背景音乐*/
    BGM = AudioEngine::play2d("bkMusic.mp3", true, 0.5f);

    auto volumeUpLab = Label::createWithTTF("+", "fonts/arial.ttf", 36);
    auto volumeDownLab = Label::createWithTTF("-", "fonts/arial.ttf", 36);
    auto vol = Label::createWithTTF("BGM", "fonts/arial.ttf", 24);
    auto volumeUpMenu = MenuItemLabel::create(volumeUpLab, CC_CALLBACK_1(initScene::menuCloseCallbackVolumeUp, this));
    auto volumeDownMenu = MenuItemLabel::create(volumeDownLab, CC_CALLBACK_1(initScene::menuCloseCallbackVolumeDown, this));

    MenuUpVolume = Menu::create(volumeUpMenu, NULL);
    MenuDownVolume = Menu::create(volumeDownMenu, NULL);

    MenuUpVolume->setPosition(visibleSize.width + origin.x - 120, visibleSize.height + origin.y - 25);
    MenuDownVolume->setPosition(visibleSize.width + origin.x - 200, visibleSize.height + origin.y - 25);
    vol->setPosition(visibleSize.width + origin.x - 160, visibleSize.height + origin.y - 25);
    this->addChild(MenuUpVolume, 5);
    this->addChild(MenuDownVolume, 5);
    this->addChild(vol, 5);

    /*创建菜单*/

    char* Start = G2U("开始游戏");
    char* Quit = G2U("结束游戏");
    auto startLab = Label::createWithTTF(Start, "fonts/Song.ttf", 36);
    auto quitLab = Label::createWithTTF(Quit, "fonts/Song.ttf", 36);

    auto startMenu = MenuItemLabel::create(startLab, CC_CALLBACK_1(initScene::menuCloseCallbackStart, this));
    auto quitMenu = MenuItemLabel::create(quitLab, CC_CALLBACK_1(initScene::menuCloseCallbackEnd, this));

    auto setPng = MenuItemImage::create(
        "information.png",
        "information.png",
        CC_CALLBACK_1(initScene::menuCloseCallbackSet, this));
    setPng->setScale(0.2f, 0.2f);
    auto quitPng = MenuItemImage::create(
        "quit.png",
        "quit.png",
        CC_CALLBACK_1(initScene::menuCloseCallbackEnd, this));
    quitPng->setScale(0.4f, 0.4f);
    auto Menu_1 = Menu::create(startMenu, quitMenu, NULL);
    auto Menu_2 = Menu::create(setPng, NULL);
    auto Menu_3 = Menu::create(quitPng, NULL);

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
    AudioEngine::stop(BGM);
    Director::getInstance()->pushScene(initScene::create());
    Director::getInstance()->replaceScene(TransitionSlideInT::create(1.8f, secureRoom::createScene()));
}

/*进入设置面板*/
void initScene::menuCloseCallbackSet(Ref* pSender)
{
    Director::getInstance()->pushScene(TransitionFade::create(0.5f, settingScene::createScene()));
}

/*升高音量*/
void initScene::menuCloseCallbackVolumeUp(Ref* pSender) {
    /*检测是否达到最大值*/
    //if (volume == 1.0f) {
    //    return;
    //}
    auto volume = AudioEngine::getVolume(BGM);
    /*修改音量*/
    AudioEngine::setVolume(BGM, volume + 0.05f);

}

/*降低音量*/
void initScene::menuCloseCallbackVolumeDown(Ref* pSender) {
    /*检测是否达到最小值*/
    //if (volume == 0.0f) {
    //    return;
    //}
    auto volume = AudioEngine::getVolume(BGM);
    /*修改音量*/
    AudioEngine::setVolume(BGM, volume - 0.05f);

}