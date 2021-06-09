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

    ////创建监听器分别监听键盘和鼠标事件
    ///* 生成子弹 */
    //auto mouseListener = EventListenerTouchOneByOne::create();
    //// 定义回调函数onTouchBegan():手指第一次碰到屏幕时被调用。
    //mouseListener->onTouchBegan = CC_CALLBACK_2(set_scene::onTouchBegan, this);
    //// 使用EventDispatcher来处理各种各样的事件，如触摸和其他键盘事件。
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, me);



    return true;
}

/* 检测鼠标互动(与触屏类似)并生成子弹 */
//bool set_scene::onTouchBegan(Touch* touch, Event* unused_event) {
//    // 1 - Just an example for how to get the player object
//    // 2.获取触摸点的坐标，并计算这个点相对于玩家的偏移量。
//    Vec2 touchLocation = touch->getLocation();
//    Vec2 offset = touchLocation - me->getPosition();
//
//    //在玩家所在的位置创建一个子弹，将其添加到场景中。
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
//    // 将偏移量转化为单位向量，即长度为1的向量。
//    offset.normalize();
//    // 将其乘以1000，你就获得了一个指向用户触屏方向的长度为1000的向量。为什么是1000呢？因为长度应当足以超过当前分辨率下屏幕的边界。
//    auto shootAmount = offset * 1000;
//    // 将此向量添加到子弹的位置上去，这样你就有了一个目标位置。
//    auto realDest = shootAmount + bullet->getPosition();
//
//    // 创建一个动作，将子弹在2秒内移动到目标位置，然后将它从场景中移除。
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

