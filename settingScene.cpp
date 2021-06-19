#include "settingScene.h"
#include "initScene.h"
#include "AudioEngine.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;

Scene* settingScene::createScene() { return settingScene::create(); }
//cocos�����ĵ����ṩ���������ڰ���
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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    /*�����˵�*/
    auto bkMusicLab = Label::createWithTTF("Background Music : ", "fonts/Marker Felt.ttf", 36);

    /*ON��OFF�˵��ڵ��ʱ���л�*/
    auto changeLabOn = Label::createWithTTF("ON", "fonts/Marker Felt.ttf", 72);
    auto changeLabOff = Label::createWithTTF("OFF", "fonts/Marker Felt.ttf", 72);

    auto exitImg = MenuItemImage::create(
        "exit.png",
        "exit.png",
        CC_CALLBACK_1(settingScene::menuCloseCallbackEnd, this));
    exitImg->setScale(0.4f, 0.4f);
    auto Menu_off = Menu::create(exitImg, NULL);
    Menu_off->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);
    this->addChild(Menu_off, 1);

    auto changeMenuOn = MenuItemLabel::create(changeLabOn, CC_CALLBACK_1(settingScene::menuCloseCallbackChange, this));
    auto changeMenuOff = MenuItemLabel::create(changeLabOff, CC_CALLBACK_1(settingScene::menuCloseCallbackChange, this));

    Menu01 = Menu::create(changeMenuOn, NULL);
    Menu02 = Menu::create(changeMenuOff, NULL);

    bkMusicLab->setPosition(visibleSize.width/2, visibleSize.width / 2);
    Menu01->setPosition(visibleSize.width / 2, visibleSize.width / 2-80);
    Menu02->setPosition(visibleSize.width / 2, visibleSize.width / 2 - 80);

    this->addChild(bkMusicLab, 1);
    this->addChild(Menu01, 1);
    this->addChild(Menu02, 1);


    /*�޸�ON/OFF״̬*/
    if (AudioEngine::isEnabled()) {
        Menu01->setVisible(true);
        Menu02->setVisible(false);
    }
    else {
        Menu01->setVisible(false);
        Menu02->setVisible(true);
    }

    return true;
}

/*�ر��������Ļص�*/
void settingScene::menuCloseCallbackEnd(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/*�ı䱳�����ֲ���״̬�Ļص�*/
void settingScene::menuCloseCallbackChange(Ref* pSender)
{
    /*�л�On��off�˵�����ʾ״̬*/
    Menu01->setVisible(1 - (Menu01->isVisible()));
    Menu02->setVisible(1 - (Menu02->isVisible()));


    /*�л����ֵĲ���״̬*/
    if (Menu01->isVisible()) {
        AudioEngine::resumeAll();
    }
    else {
        AudioEngine::pauseAll();
    }
}