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

    m_tileMap = TMXTiledMap::create("pic.tmx");
    m_tileMap->setPosition(winSize.width * 0, winSize.height * 0);
    this->addChild(m_tileMap);

    heroForTest = hero::create();
    heroForTest->initMemHero("knight1.png", 0.0f, 3, 10, 0.0f);
    heroForTest->getSprite()->setScale(0.1f);
    heroForTest->getSprite()->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
    this->addChild(heroForTest->getSprite(), 5);
    this->scheduleUpdate();
    //me->setScale(0.1f);
    //me->setPosition(winSize.width * 0.5f, winSize.height * 0.5f);
    //this->addChild(me,5);
    /********************************************************************/
    //auto bulletForTest = bullet::createBullet("bullet_1.png");
    //auto weaponForTest = rangedWeapon::createRangedWeapon("SubmachineGun.png", bulletForTest);
    //weaponForTest->getSpriteInRangedWeapon()->setScale(0.2);
    //weaponForTest->getSpriteInRangedWeapon()->setPosition(me->getPosition());
    //m_tileMap->addChild(weaponForTest->getSpriteInRangedWeapon(), 6);
    //
    //auto moveby = MoveBy::create(0.01f, Vec2(200, 0));
    //me->runAction(moveby);
    //
    //auto weaponForTest2 = rangedWeapon::createRangedWeapon("SubmachineGun2.png", bulletForTest);
    //weaponForTest2->getSpriteInRangedWeapon()->setScale(0.2);
    //weaponForTest2->getSpriteInRangedWeapon()->setPosition(me->getPosition());
    //weaponForTest = weaponForTest2;
    //m_tileMap->addChild(weaponForTest->getSpriteInRangedWeapon(), 6);
    //bulletForTest->getSpriteInBullet()->setPosition(me->getPosition());
    //m_tileMap->addChild(bulletForTest->getSpriteInBullet(), 6);
    //auto SpriteCache = SpriteFrameCache::getInstance();
    //SpriteCache->addSpriteFramesWithFile("BigKnife.plist");
    //auto weaponForTest = bullet::createBullet("BigKnife0.png");
    //weaponForTest->setScale(0.2f);
    //weaponForTest->setPosition(me->getPosition());
    //this->addChild(weaponForTest.get(),6);
    /********************************************************************/

    ////�����������ֱ�������̺�����¼�
    ///* �����ӵ� */
    //auto mouseListener = EventListenerTouchOneByOne::create();
    //// ����ص�����onTouchBegan():��ָ��һ��������Ļʱ�����á�
    //mouseListener->onTouchBegan = CC_CALLBACK_2(set_scene::onTouchBegan, this);
    //// ʹ��EventDispatcher��������ָ������¼����紥�������������¼���
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, me);



    return true;
}

/* �����껥��(�봥������)�������ӵ� */
//bool set_scene::onTouchBegan(Touch* touch, Event* unused_event) {
//    // 1 - Just an example for how to get the player object
//    // 2.��ȡ����������꣬������������������ҵ�ƫ������
//    Vec2 touchLocation = touch->getLocation();
//    Vec2 offset = touchLocation - me->getPosition();
//
//    //��������ڵ�λ�ô���һ���ӵ���������ӵ������С�
//    auto bullet = Sprite::create("bullet_1.png");
//    bullet->setPosition(me->getPosition());
//    //// Add projectile's physicsBody
//    //auto physicsBody = PhysicsBody::createBox(bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
//    //physicsBody->setDynamic(false);
//    //physicsBody->setContactTestBitmask(0xFFFFFFFF);
//    //bullet->setPhysicsBody(physicsBody);
//    //bullet->setTag(10);
//    ////Add projectile's physicsBody
//    this->addChild(bullet);
//
//    // ��ƫ����ת��Ϊ��λ������������Ϊ1��������
//    offset.normalize();
//    // �������1000����ͻ����һ��ָ���û���������ĳ���Ϊ1000��������Ϊʲô��1000�أ���Ϊ����Ӧ�����Գ�����ǰ�ֱ�������Ļ�ı߽硣
//    auto shootAmount = offset * 1000;
//    // ����������ӵ��ӵ���λ����ȥ�������������һ��Ŀ��λ�á�
//    auto realDest = shootAmount + bullet->getPosition();
//
//    // ����һ�����������ӵ���2�����ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ���
//    auto actionMove = MoveTo::create(2.0f, realDest);
//    auto actionRemove = RemoveSelf::create();
//    bullet->runAction(Sequence::create(actionMove, actionRemove, nullptr));
//
//    return true;
//}
//
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

void set_scene::update(float delta)
{
    //auto right = (EventKeyboard::KeyCode)127;
    //auto left = (EventKeyboard::KeyCode)124;
    //auto up = (EventKeyboard::KeyCode)146;
    //auto down = (EventKeyboard::KeyCode)142;

    //if (keyMap[right])
    //{
    //    auto moveby = MoveBy::create(0.01f, Vec2(7,0));
    //    me->runAction(moveby);
    //}

    //if (keyMap[left])
    //{
    //    auto moveby = MoveBy::create(0.01f, Vec2(-7,0));
    //    me->runAction(moveby);
    //}
    //if (keyMap[up])
    //{
    //    auto moveby = MoveBy::create(0.01f, Vec2(0,7));
    //    me->runAction(moveby);
    //}

    //if (keyMap[down])
    //{
    //    auto moveby = MoveBy::create(0.01f, Vec2(0,-7));
    //    me->runAction(moveby);
    //}
}

