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

    // ˳�����ﻮ�ص㣡���� ��������Ҳ�֪���ǲ�����д�� ����ϵͳ���� ���������set_scene.cpp���� �㿴һ������ļ�
    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(set_scene);
private:
    monster* monsterfort;
    hero* heroForTest;
    cocos2d::TMXTiledMap* m_tileMap;
    short direction;
};


