#include "settingScene.h"
#include "initScene.h"
#include "AudioEngine.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;

Scene* settingScene::createScene() { return settingScene::create(); }
//cocos测试文档中提供的声音调节案例
class SliderEx : public Slider
{
public:
    static SliderEx* create() {
        auto ret = new (std::nothrow) SliderEx();
        if (ret && ret->init())
        {
            ret->loadBarTexture("settings/sliderTrack.png");
            ret->loadSlidBallTextures("settings/sliderThumb.png", "settings/sliderThumb.png", "");
            ret->loadProgressBarTexture("settings/sliderProgress.png");
            ret->setTouchEnabled(true);
            ret->autorelease();

            return ret;
        }
        CC_SAFE_DELETE(ret);
        return ret;
    }

    void setRatio(float ratio) {
        ratio = clampf(ratio, 0.0f, 1.0f);

        _ratio = ratio;
        setPercent(100 * _ratio);
    }

    float getRatio() {
        _ratio = 1.0f * _percent / _maxPercent;
        return _ratio;
    }

private:
    float _ratio;
};

//转换中文
char* settingScene::G2U(const char* gb2312)
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

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool settingScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //创建地图
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取安全屋大小

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backGround = Sprite::create("introduce.png");
    auto backGroundSize = backGround->getContentSize();
    backGround->setScale(visibleSize.width / backGroundSize.width, visibleSize.height / backGroundSize.height);

    backGround->setPosition(
        Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backGround, 0);

    audio = AudioEngine::play2d("BGM/none.mp3", true) - 1;
    //创建BGM开关部分
    char* BGM_ON = G2U("开");
    char* BGM_OFF = G2U("关");
    char* _BGM = G2U("背景音乐: ");
    auto bkMusicLab = Label::createWithTTF(_BGM, "fonts/Song.ttf", 36);

    /*ON，OFF菜单在点击时会切换*/
    auto LabelOn = Label::createWithTTF(BGM_ON, "fonts/Song.ttf", 36);
    auto LabelOff = Label::createWithTTF(BGM_OFF, "fonts/Song.ttf", 36);

    auto quitPng = MenuItemImage::create(
        "quit.png",
        "quit.png",
        CC_CALLBACK_1(settingScene::menuCloseCallbackEnd, this));
    quitPng->setScale(0.4f, 0.4f);
    auto Menu_off = Menu::create(quitPng, NULL);
    Menu_off->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);
    this->addChild(Menu_off, 1);

    auto turnMenuOn = MenuItemLabel::create(LabelOn, CC_CALLBACK_1(settingScene::menuCloseCallbackChange, this));
    auto turnMenuOff = MenuItemLabel::create(LabelOff, CC_CALLBACK_1(settingScene::menuCloseCallbackChange, this));

    Menu_On = Menu::create(turnMenuOn, NULL);
    Menu_Off = Menu::create(turnMenuOff, NULL);

    bkMusicLab->setPosition(visibleSize.width / 8 * 7, visibleSize.width / 9);
    Menu_On->setPosition(visibleSize.width / 8 * 7 - 20, visibleSize.width / 15);
    Menu_Off->setPosition(visibleSize.width / 8 * 7 - 20, visibleSize.width / 15);

    this->addChild(bkMusicLab, 1);
    this->addChild(Menu_On, 1);
    this->addChild(Menu_Off, 1);



    /*修改ON/OFF状态*/
    if (AudioEngine::isEnabled()) {
        Menu_On->setVisible(true);
        Menu_Off->setVisible(false);
    }
    else {
        Menu_On->setVisible(false);
        Menu_Off->setVisible(true);
    }

    return true;
}

/*关闭设置面板的回调*/
void settingScene::menuCloseCallbackEnd(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/*改变背景音乐播放状态的回调*/
void settingScene::menuCloseCallbackChange(Ref* pSender)
{
    /*切换On，off菜单的显示状态*/
    Menu_On->setVisible(1 - (Menu_On->isVisible()));
    Menu_Off->setVisible(1 - (Menu_Off->isVisible()));


    /*切换音乐的播放状态*/
    if (Menu_On->isVisible()) {
        AudioEngine::resumeAll();
    }
    else {
        AudioEngine::pauseAll();
    }
}
