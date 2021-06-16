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

    auto volumeLab = Label::createWithTTF("Volume:", "fonts/arial.ttf", 36);
    volumeLab->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
    this->addChild(volumeLab, 0);
    //官方测试文档提供的声音调节案例
    auto _audioID = AudioEngine::INVALID_AUDIO_ID;
    auto volumeSlider = SliderEx::create();
    volumeSlider->setPercent(100);
    volumeSlider->addEventListener([&](Ref* sender, Slider::EventType event) {
        SliderEx* slider = dynamic_cast<SliderEx*>(sender);
        auto _volume = slider->getRatio();
        if (_audioID != AudioEngine::INVALID_AUDIO_ID) {
            AudioEngine::setVolume(_audioID, _volume);
        }
        });
    volumeSlider->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.35f + origin.y));
    this->addChild(volumeSlider, 2);
    auto exitImg = MenuItemImage::create(
        "exit.png",
        "exit.png",
        CC_CALLBACK_1(settingScene::menuCloseCallbackEnd, this));

    auto Menu_off = Menu::create(exitImg, NULL);
    Menu_off->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);
    this->addChild(Menu_off, 1);
}

/*关闭设置面板的回调*/
void settingScene::menuCloseCallbackEnd(Ref* pSender)
{
    Director::getInstance()->popScene();
}