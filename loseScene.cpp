#include "loseScene.h"
#include "initScene.h"
#include "AudioEngine.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;

Scene* loseScene::createScene() { return loseScene::create(); }

//ת������
char* loseScene::G2U(const char* gb2312)
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
bool loseScene::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //������ͼ
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��ȫ�ݴ�С

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    backGround = Sprite::create("lose.png");
    auto backGroundSize = backGround->getContentSize();
    backGround->setScale(visibleSize.width / backGroundSize.width, visibleSize.height / backGroundSize.height);

    backGround->setPosition(
        Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backGround, 0);

    //����BGM���ز���
    char* BGM_ON = G2U("��");
    char* BGM_OFF = G2U("��");
    char* _BGM = G2U("��������: ");
    auto bkMusicLab = Label::createWithTTF(_BGM, "fonts/Song.ttf", 36);

    /*ON��OFF�˵��ڵ��ʱ���л�*/
    auto LabelOn = Label::createWithTTF(BGM_ON, "fonts/Song.ttf", 36);
    auto LabelOff = Label::createWithTTF(BGM_OFF, "fonts/Song.ttf", 36);

    auto quitPng = MenuItemImage::create(
        "quit.png",
        "quit.png",
        CC_CALLBACK_1(loseScene::menuCloseCallbackEnd, this));
    quitPng->setScale(0.4f, 0.4f);
    auto Menu_off = Menu::create(quitPng, NULL);
    Menu_off->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);
    this->addChild(Menu_off, 1);

    auto turnMenuOn = MenuItemLabel::create(LabelOn, CC_CALLBACK_1(loseScene::menuCloseCallbackChange, this));
    auto turnMenuOff = MenuItemLabel::create(LabelOff, CC_CALLBACK_1(loseScene::menuCloseCallbackChange, this));

    Menu_On = Menu::create(turnMenuOn, NULL);
    Menu_Off = Menu::create(turnMenuOff, NULL);

    bkMusicLab->setPosition(visibleSize.width / 8 * 7, visibleSize.width / 9);
    Menu_On->setPosition(visibleSize.width / 8 * 7 - 20, visibleSize.width / 15);
    Menu_Off->setPosition(visibleSize.width / 8 * 7 - 20, visibleSize.width / 15);

    this->addChild(bkMusicLab, 1);
    this->addChild(Menu_On, 1);
    this->addChild(Menu_Off, 1);



    /*�޸�ON/OFF״̬*/
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

/*�ر��������Ļص�*/
void loseScene::menuCloseCallbackEnd(Ref* pSender)
{
    Director::getInstance()->popScene();
}
/*�ı䱳�����ֲ���״̬�Ļص�*/
void loseScene::menuCloseCallbackChange(Ref* pSender)
{
    /*�л�On��off�˵�����ʾ״̬*/
    Menu_On->setVisible(1 - (Menu_On->isVisible()));
    Menu_Off->setVisible(1 - (Menu_Off->isVisible()));


    /*�л����ֵĲ���״̬*/
    if (Menu_On->isVisible()) {
        AudioEngine::resumeAll();
    }
    else {
        AudioEngine::pauseAll();
    }
}
