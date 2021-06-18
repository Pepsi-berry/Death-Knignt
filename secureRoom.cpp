#include "secureRoom.h"
#include "ui/CocosGUI.h"
//#include "hero.h"
#include "battleScene.h"

hero* battleScene::Hero = nullptr;
int battleScene::_battleSceneNumber = 0;
int battleScene::_heroStateType = 0;
int battleScene::_heroStateHP = 0;
int battleScene::_heroStateArmor = 0;
int battleScene::_heroStateWeaponType = 0;



void secureRoom::truekeycode(EventKeyboard::KeyCode keycode)
{
	keyMap[keycode] = true;
}

void secureRoom::falsekeycode(EventKeyboard::KeyCode keycode)
{
	keyMap[keycode] = false;
}


void secureRoom::updatekeyboard(float delta)
{
	if (ischosen == 0)
	{
		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*)
		{
			this->truekeycode(code);
		};

		listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
			this->falsekeycode(code);
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
}


Scene* secureRoom::createScene() {
	Scene* scene = Scene::createWithPhysics();
	//设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	secureRoom* layer = secureRoom::create();
	//把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}


void secureRoom::update(float delta) 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (ischosen == 0)
	{
		if (keyMap[EventKeyboard::KeyCode::KEY_J])
		{
			Hero = hero::create();
			Hero->setHeroType(1);
			Hero->initmem();
			Hero->bindscene(this);
			Hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
			PhysicsBody* herobody = PhysicsBody::createBox(Hero->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
			herobody->setGravityEnable(false);
			herobody->setDynamic(false);
			herobody->setCategoryBitmask(0x0001);
			herobody->setCollisionBitmask(0x0001);
			herobody->setContactTestBitmask(0x0001);
			Hero->addComponent(herobody);
			Hero->setTag(1);
			auto myweapon = weapon::create();
			myweapon->changeWeapon(0);
			Hero->bindWeapon(myweapon);
			this->addChild(Hero, 0);
			ischosen = 1;
		}
		if (keyMap[EventKeyboard::KeyCode::KEY_K])
		{
			Hero = hero::create();
			Hero->setHeroType(2);
			Hero->initmem();
			Hero->bindscene(this);
			Hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
			PhysicsBody* herobody = PhysicsBody::createBox(Hero->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
			herobody->setGravityEnable(false);
			herobody->setDynamic(false);
			herobody->setCategoryBitmask(0x0001);
			herobody->setCollisionBitmask(0x0001);
			herobody->setContactTestBitmask(0x0001);
			Hero->addComponent(herobody);
			Hero->setTag(1);
			auto myweapon = weapon::create();
			myweapon->changeWeapon(1);
			Hero->bindWeapon(myweapon);
			this->addChild(Hero, 0);
			ischosen = 1;
		}
	}
	if (ischosen == 1)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		float movingSpeedX = Hero->getmovespeedX();
		float movingSpeedY = Hero->getmovespeedY();

		float curPositionX = Hero->getPositionX();
		float curPositionY = Hero->getPositionY();

		Hero->setPosition(curPositionX + movingSpeedX, curPositionY + movingSpeedY);

		if (isInDoor())
		{
			battleScene::Hero = this->Hero;
			battleScene::Hero->retain();
			battleScene::Hero->removeFromParent();
			battleScene::_battleSceneNumber = 1;
			battleScene::_heroStateType = this->Hero->getHeroType();
			battleScene::_heroStateHP = this->Hero->getHP();
			battleScene::_heroStateArmor = this->Hero->getArmor();
			battleScene::_heroStateWeaponType = this->Hero->getCurWeapon()->getWeaponType();


			this->cleanup();
			this->removeAllChildren();

			Director::getInstance()->replaceScene(TransitionSlideInT::create(1.8f, battleScene::createBattleScene()));
		}
	}
}

bool secureRoom::init() {
	if (!Scene::init()) {
		return false;
	}
	//创建地图
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//获取安全屋大小

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->backGround = Sprite::create("SecureRoom.png");
	auto backGroundSize = this->backGround->getContentSize();
	this->backGround->setScale(visibleSize.width / backGroundSize.width, visibleSize.height / backGroundSize.height);

	this->backGround->setPosition(
		Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(this->backGround, 0);

	////设置与退出组件
	//auto setImg = MenuItemImage::create(
	//	"set.png",
	//	"set.png",
	//	CC_CALLBACK_1(SecureMap::menuCloseCallbackSet, this));
	//auto exitImg = MenuItemImage::create(
	//	"exit.png",
	//	"exit.png",
	//	CC_CALLBACK_1(SecureMap::menuCloseCallbackEnd, this));

	//auto Menu_2 = Menu::create(setImg, NULL);
	//auto Menu_3 = Menu::create(exitImg, NULL);

	//Menu_2->setPosition(visibleSize.width + origin.x - 75, visibleSize.height + origin.y - 25);
	//Menu_3->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);

	//this->addChild(Menu_2, 1);
	//this->addChild(Menu_3, 1);
	// 
	// 
	//英雄初始化
	this->schedule(CC_SCHEDULE_SELECTOR(secureRoom::updatekeyboard), 0.01f);
	this->scheduleUpdate();

	return true;
}



void secureRoom::menuCloseCallbackEnd(Ref* pSender) 
{
	Director::getInstance()->popScene();
}
//
///*进入设置面板*/
//void secureRoom::menuCloseCallbackSet(Ref* pSender)
//{
//	Director::getInstance()->pushScene(TransitionFade::create(2.0f, settingScene::createScene()));
//}

bool secureRoom::isInDoor() {
	float CurX = Hero->getPositionX(), CurY = Hero->getPositionY();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*位置界定*/
	if (CurX >= visibleSize.width/2-10 && CurX <= visibleSize.width / 2 + 50 && CurY >= visibleSize.height-70 && CurY <= visibleSize.width+40) {
		return 1;
	}
	else 
	{
		return 0;
	}
}