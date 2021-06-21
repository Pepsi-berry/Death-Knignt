#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "battleScene.h"
#include "settingScene.h"
#include "initScene.h"
#include <cmath>
#include"loseScene.h"
#include "AudioEngine.h"
//#include "set_scene.h"

//hero* battleScene::Hero = nullptr;
//int battleScene::_battleSceneNumber = 1;

//void battleScene::bindmonster(monster* mons)
//{
//	monsterforT = mons;
//}
//
//monster* battleScene::getmonster()
//{
//	return monsterforT;
//}

Scene* battleScene::createBattleScene()
{
	Scene* scene = Scene::createWithPhysics();
	//设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察
	battleScene* layer = battleScene::create();
	//把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}


bool battleScene::init()
{
	if (!Scene::init())
		return false;

	//bgm启动
	AudioEngine::stopAll();
	randomBGM();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	initBattleRoomGenerate(); 
	connectRoom(_beginRoom); 

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*背景音乐*/

	auto volumeUpLab = Label::createWithTTF("+", "fonts/arial.ttf", 36);
	auto volumeDownLab = Label::createWithTTF("-", "fonts/arial.ttf", 36);
	auto vol = Label::createWithTTF("BGM", "fonts/arial.ttf", 24);
	auto volumeUpMenu = MenuItemLabel::create(volumeUpLab, CC_CALLBACK_1(battleScene::menuCloseCallbackVolumeUp, this));
	auto volumeDownMenu = MenuItemLabel::create(volumeDownLab, CC_CALLBACK_1(battleScene::menuCloseCallbackVolumeDown, this));

	MenuUpVolume = Menu::create(volumeUpMenu, NULL);
	MenuDownVolume = Menu::create(volumeDownMenu, NULL);

	MenuUpVolume->setPosition(visibleSize.width + origin.x - 120, visibleSize.height + origin.y - 25);
	MenuDownVolume->setPosition(visibleSize.width + origin.x - 200, visibleSize.height + origin.y - 25);
	vol->setPosition(visibleSize.width + origin.x - 160, visibleSize.height + origin.y - 25);
	this->addChild(MenuUpVolume, 5);
	this->addChild(MenuDownVolume, 5);
	this->addChild(vol, 5);

	//状态条的更新
	HPLoadingBar = ui::LoadingBar::create("Character/StatusBlood.png");
	HPLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	auto statusFrame = Sprite::create("Character/StatusBackground.png");
	HPnum = Label::createWithTTF("0", "fonts/arial.ttf", 15);

	ARMORLoadingBar = ui::LoadingBar::create("Character/StatusArmor.png");
	ARMORLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	ARMORnum = Label::createWithTTF("0", "fonts/arial.ttf", 15);

	MPLoadingBar = ui::LoadingBar::create("Character/StatusMP.png");
	MPLoadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	MPnum = Label::createWithTTF("0", "fonts/arial.ttf", 15);

	COINnum = Label::createWithTTF("100", "fonts/arial.ttf", 22);
	CoinPng = Sprite::create("Props/add_gold.png");

	statusFrame->setPosition(origin.x + 60, visibleSize.height + origin.y - 30);
	HPLoadingBar->setPosition(Vec2(origin.x + 69, visibleSize.height + origin.y - 10));
	HPnum->setPosition(Vec2(origin.x + 69, visibleSize.height + origin.y - 10));

	ARMORLoadingBar->setPosition(Vec2(origin.x + 69, visibleSize.height + origin.y - 27));
	ARMORnum->setPosition(Vec2(origin.x + 69, visibleSize.height + origin.y - 27));

	MPLoadingBar->setPosition(Vec2(origin.x + 69, visibleSize.height + origin.y - 44));
	MPnum->setPosition(Vec2(origin.x + 69, visibleSize.height + origin.y - 44));

	COINnum->setPosition(Vec2(origin.x + 200, visibleSize.height + origin.y - 30));
	CoinPng->setPosition(Vec2(origin.x + 160, visibleSize.height + origin.y - 30));
	this->addChild(statusFrame, 10);

	this->addChild(HPLoadingBar, 65536);
	this->addChild(ARMORLoadingBar, 65536);
	this->addChild(MPLoadingBar, 65536);

	this->addChild(HPnum, 65536);
	this->addChild(ARMORnum, 65536);
	this->addChild(MPnum, 65536);

	this->addChild(COINnum, 65536);
	this->addChild(CoinPng, 65536);

	//初始化图标
	auto quitImg = MenuItemImage::create(
		"quit.png",
		"quit.png",
		CC_CALLBACK_1(battleScene::menuCloseCallbackEnd, this));
	quitImg->setScale(0.4f, 0.4f);

	auto setImg = MenuItemImage::create(
		"information.png",
		"information.png",
		CC_CALLBACK_1(battleScene::menuCloseCallbackSet, this));
	setImg->setScale(0.2f, 0.2f);

	auto quitMenu = Menu::create(quitImg, NULL);
	auto setMenu = Menu::create(setImg, NULL);
	quitMenu->setPosition(visibleSize.width + origin.x - 28, visibleSize.height + origin.y - 25);
	setMenu->setPosition(visibleSize.width + origin.x - 75, visibleSize.height + origin.y - 25);
	this->addChild(quitMenu, 50);
	this->addChild(setMenu, 50);


	//后期考虑将下述添加过程做函数拆分工作
	//添加英雄并对其完成初始化
	Hero = hero::create();
	Hero->setHeroType(_heroStateType);
	Hero->initmem();
	Hero->setHP(_heroStateHP);
	Hero->setMP(_heroStateMP);
	Hero->setArmor(_heroStateArmor);
	Hero->setCoin(_heroStateCoin);
	Hero->setCurWeaponType(_heroStateCurWeaponType);
	Hero->setSecondaryWeaponType(_heroStateSecondaryWeaponType);
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
	Hero->setmovespeedX(.0f);
	Hero->setmovespeedY(.0f);

	Hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	// add knight to scene

	//auto myweapon = weapon::create();
	//myweapon->changeWeapon(_heroStateWeaponType);
	//auto myweapon2 = weapon::create();
	//myweapon2->changeWeapon(3);
	Hero->bindWeapon();
	//Hero->bindSecondaryWeapon(myweapon2);
	this->addChild(Hero, 0);


	initEnemy();

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(battleScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(battleScene::updateMonsterAttack), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(battleScene::updateHeroArmor), 1.0f);
	this->schedule(CC_SCHEDULE_SELECTOR(battleScene::updateSkillCooling), 1.0f);

	return true;
}

bool battleScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	hero* hero1;
	monster* monster1;
	bullet* bullet1;
	Sprite* arrow1;
	boss* boss1;
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeB->getTag() == 2 && nodeA->getTag() == 1)
		{
			monster1 = dynamic_cast<monster*>(nodeB);
			hero1 = dynamic_cast<hero*>(nodeA);
			if (monster1->canattack == true)
			{
				hero1->getdamage(monster1->getmydamage());
				_recoveryCoolingTime = 0;
			}
			if (hero1->isdead())
				hero1->removeAllComponents();
		}
		else if (nodeA->getTag() == 2 && nodeB->getTag() == 1)
		{
			monster1 = dynamic_cast<monster*>(nodeA);
			hero1 = dynamic_cast<hero*>(nodeB);
			if (monster1->canattack == true)
			{
				hero1->getdamage(monster1->getmydamage());
				_recoveryCoolingTime = 0;
			}
			if (hero1->isdead())
				hero1->removeAllComponents();
		}
		else if (nodeA->getTag() == 2 && nodeB->getTag() == 3)
		{
			monster1 = dynamic_cast<monster*>(nodeA);
			bullet1 = dynamic_cast<bullet*>(nodeB);
			monster1->getdamage(bullet1->getdamage());
			if (monster1->isdead())
			{
				if (rand() % 20 == 0)
				{
					auto randdrop = drop::create();
					randdrop->changetype(rand() % 3);
					randdrop->setPosition(monster1->getPosition());
					Hero->getCurBattleRoom()->getVecdrop().pushBack(randdrop);
					Hero->getCurBattleRoom()->addChild(randdrop);
				}
				Hero->addCoin(rand() % 4);
				monster1->removeAllComponents();
			}
			bullet1->removeAllComponents();
			auto actionRemove = RemoveSelf::create();
			bullet1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 3 && nodeB->getTag() == 2)
		{
			monster1 = dynamic_cast<monster*>(nodeB);
			bullet1 = dynamic_cast<bullet*>(nodeA);
			monster1->getdamage(bullet1->getdamage());
			if (monster1->isdead())
			{
				if (rand() % 20 == 0)
				{
					auto randdrop = drop::create();
					randdrop->changetype(rand() % 3);
					randdrop->setPosition(monster1->getPosition());
					Hero->getCurBattleRoom()->getVecdrop().pushBack(randdrop);
					Hero->getCurBattleRoom()->addChild(randdrop);
				}
				Hero->addCoin(rand() % 4);
				monster1->removeAllComponents();
			}
			bullet1->removeAllComponents();
			auto actionRemove = RemoveSelf::create();
			bullet1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 1 && nodeB->getTag() == 4)
		{
			hero1 = dynamic_cast<hero*>(nodeA);
			arrow1 = dynamic_cast<Sprite*>(nodeB);
			hero1->getdamage(1);
			_recoveryCoolingTime = 0;
			if (hero1->isdead())
				hero1->removeAllComponents();
			arrow1->removeAllComponents();
			auto actionRemove = RemoveSelf::create();
			arrow1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 4 && nodeB->getTag() == 1)
		{
			hero1 = dynamic_cast<hero*>(nodeB);
			arrow1 = dynamic_cast<Sprite*>(nodeA);
			hero1->getdamage(1);
			_recoveryCoolingTime = 0;
			if (hero1->isdead())
				hero1->removeAllComponents();
			arrow1->removeAllComponents();
			auto actionRemove = RemoveSelf::create();
			arrow1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 9 && nodeB->getTag() == 3)
		{
			boss1 = dynamic_cast<boss*>(nodeA);
			bullet1 = dynamic_cast<bullet*>(nodeB);
			boss1->getdamage(bullet1->getdamage());
			if (boss1->isdead())
			{
				Hero->addCoin(rand() % 10 + 10);
				boss1->removeAllComponents();
			}
			bullet1->removeAllComponents();
			auto actionRemove = RemoveSelf::create();
			bullet1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 3 && nodeB->getTag() == 9)
		{
			boss1 = dynamic_cast<boss*>(nodeB);
			bullet1 = dynamic_cast<bullet*>(nodeA);
			boss1->getdamage(bullet1->getdamage());
			if (boss1->isdead())
			{
				Hero->addCoin(rand() % 10 + 10);
				boss1->removeAllComponents();
			}
			bullet1->removeAllComponents();
			auto actionRemove = RemoveSelf::create();
			bullet1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 1 && nodeB->getTag() == 10)
		{
		hero1 = dynamic_cast<hero*>(nodeA);
		arrow1 = dynamic_cast<Sprite*>(nodeB);
		hero1->getdamage(3);
		if (hero1->isdead())
			hero1->removeAllComponents();
		arrow1->removeAllComponents();
		auto actionRemove = RemoveSelf::create();
		arrow1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 10 && nodeB->getTag() == 1)
		{
		hero1 = dynamic_cast<hero*>(nodeB);
		arrow1 = dynamic_cast<Sprite*>(nodeA);
		hero1->getdamage(3);
		if (hero1->isdead())
			hero1->removeAllComponents();
		arrow1->removeAllComponents();
		auto actionRemove = RemoveSelf::create();
		arrow1->runAction(actionRemove);
		}
		else if (nodeA->getTag() == 1 && nodeB->getTag() == 9)
		{
		hero1 = dynamic_cast<hero*>(nodeA);
		boss1 = dynamic_cast<boss*>(nodeB);
		hero1->getdamage(3);
		if (hero1->isdead())
			hero1->removeAllComponents();
		}
		else if (nodeA->getTag() == 9 && nodeB->getTag() == 1)
		{
		hero1 = dynamic_cast<hero*>(nodeB);
		boss1 = dynamic_cast<boss*>(nodeA);
		hero1->getdamage(3);
		if (hero1->isdead())
			hero1->removeAllComponents();
		}
	}
	return true;
}

void battleScene::initEnemy()
{
	for (int y = 0; y < NumRoomY; y++)
		for (int x = 0; x < NumRoomX; x++)
		{
			auto curBattleRoom = _battleRoomMatrix[y][x];
			if (curBattleRoom == nullptr)
				continue;
			if (curBattleRoom->_battleRoomType == TypeNormal)
				curBattleRoom->createMonster();
			else if (curBattleRoom->_battleRoomType == TypeBoss)
				curBattleRoom->createBoss();
		}
}
void battleScene::update(float delta)
{
	updateGameLose();
	updateRoomHeroLocated();
	//updateBoundaryJudgement();
	updateBattleScenePosition();
	updateBattleRoomDoorState();
	updateBossState();
	updatePortalJudgement();
	if (Hero->getCurBattleRoom() != nullptr || Hero->getCurCorridor() != nullptr)
		updateUILoading();
}

void battleScene::updateUILoading()    //状态的更新
{
	HPLoadingBar->setPercent(float(this->Hero->getHP())/float(this->Hero->getMaxHP())*100.0f);
	HPnum->setString(Value(this->Hero->getHP()).asString());
	ARMORLoadingBar->setPercent(float(this->Hero->getArmor()) / float(this->Hero->getMaxArmor()) * 100.0f);
	ARMORnum->setString(Value(this->Hero->getArmor()).asString());
	MPLoadingBar->setPercent(float(this->Hero->getMP()) / float(this->Hero->getMaxMP()) * 100.0f);
	MPnum->setString(Value(this->Hero->getMP()).asString());
	COINnum->setString(Value(this->Hero->getCoin()).asString());
}

//暂时只包括视野移动
void battleScene::updateBattleScenePosition()
{

	//updateBoundaryJudgement();
	if (Hero->getCurBattleRoom() != nullptr)
		Hero->getCurBattleRoom()->checkBattleRoomBoundaryBarrier(Hero);
	else
		Hero->getCurCorridor()->checkCorridorBoundaryBarrier(Hero);

	if (Hero->isdead())
	{
		Hero->setmovespeedX(0);
		Hero->setmovespeedY(0);
	}
	float mvSpeedX = Hero->getmovespeedX();
	float mvSpeedY = Hero->getmovespeedY();

	//CCLOG("mvSpeedX%f,mvSpeedY%f", mvSpeedX, mvSpeedY);

	for (int y = 0; y < NumRoomY; y++)
	{ //修改所有子节点战斗房间位置
		for (int x = 0; x < NumRoomY; x++)
		{
			if (_battleRoomMatrix[x][y] == nullptr)
				continue;
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			curRoom->moveRoomPosition(-mvSpeedX, -mvSpeedY);
		}
	}
	for (auto corridor : vecCorridor)
		corridor->moveRoomPosition(-mvSpeedX, -mvSpeedY);

}

void battleScene::updateRoomHeroLocated()
{
	//先判断是否位于某战斗房间
	bool isAtBattleRoomOrCorridor = false;                 //储存位于走廊或战斗房间
	for (int y = 0; y < NumRoomY; y++)
		for (int x = 0; x < NumRoomX; x++)
		{
			battleRoom* curBattleRoom = _battleRoomMatrix[y][x];
			if (curBattleRoom == nullptr)
				continue;
			//CCLOG("%d,%d", y, x);
			//CCLOG("heroPositionX %f,heroPositionY %f,_topLeftCornerPositionX %f,_topLeftCornerPositionY %f, _lowerRightCornerPositionX %f,_lowerRightCornerPositionY %f",
			//	Hero->getPositionX(), Hero->getPositionY(), curBattleRoom->_topLeftCornerPositionX, curBattleRoom->_topLeftCornerPositionY, curBattleRoom->_lowerRightCornerPositionX, curBattleRoom->_lowerRightCornerPositionY);
			if (curBattleRoom->getIsAtRoom(Hero) == true)
			{
				Hero->setCurBattleRoom(curBattleRoom);
				Hero->setCurCorridor(nullptr);
				isAtBattleRoomOrCorridor = true;
				//CCLOG("%d,%d", curBattleRoom->_columnNum, curBattleRoom->_rowNum);
				//CCLOG("heroPositionX %f,heroPositionY %f,_topLeftCornerPositionX %f,_topLeftCornerPositionY %f, _lowerRightCornerPositionX %f,_lowerRightCornerPositionY %f",
				//	Hero->getPositionX(), Hero->getPositionY(), curBattleRoom->_topLeftCornerPositionX, curBattleRoom->_topLeftCornerPositionY, curBattleRoom->_lowerRightCornerPositionX, curBattleRoom->_lowerRightCornerPositionY);

				//CCLOG("%d,%d", x, y);
			}
		}
	if (isAtBattleRoomOrCorridor)
		return;
	for (room* curCorridor : vecCorridor)
	{
		if (curCorridor->getIsAtRoom(Hero))
		{
			Hero->setCurBattleRoom(nullptr);
			Hero->setCurCorridor(curCorridor);
		}
	}
}

void battleScene::updateBoundaryJudgement()
{
	;
}

void battleScene::updateMonsterAttack(float delta)
{
	Vec2 curheropos = Hero->getPosition();
	monster* nearMonster = nullptr;
	if (this->Hero->getCurBattleRoom() != nullptr)
	{
		for (monster* curMonster : this->Hero->getCurBattleRoom()->getVecMonster())
		{
			if (!curMonster->isdead())
			{
				int curMonsterType = curMonster->gettype();
				if (curMonsterType == 0|| curMonsterType == 2)
				{
					if (!Hero->isdead())
					{
						Vec2 enemyPos = curMonster->getPosition();
						if (enemyPos.distance(curheropos) < curMonster->getAttackRange())
						{
							//判定不会冲出房间时野猪发动冲撞
							float Xmin = curMonster->getAtBattleRoom()->getTopLeftCornerPositionX();
							float Ymin = curMonster->getAtBattleRoom()->getLowerRightCornerPositionY();
							float Xmax = curMonster->getAtBattleRoom()->getLowerRightCornerPositionX();
							float Ymax = curMonster->getAtBattleRoom()->getTopLeftCornerPositionY();



							float dstX;
							float dstY;
							float delat_x = Hero->getPositionX() - curMonster->getPositionX();
							float delat_y = Hero->getPositionY() - curMonster->getPositionY();
							if (delat_x != 0)
							{
								float tan = abs(delat_y / delat_x);
								float t_2 = tan * tan;
								float squr = 1 + t_2;
								float length = sqrt(squr);
								if (delat_x > 0)
									dstX = curMonster->getAttackRange() / length;
								else
									dstX = -(curMonster->getAttackRange()) / length;
								if (delat_y > 0)
									dstY = (curMonster->getAttackRange() / length) * tan;
								else
									dstY = -(curMonster->getAttackRange() / length) * tan;
								dstX = dstX + curMonster->getPositionX();
								dstY = dstY + curMonster->getPositionY();
							}
							else
							{
								dstX = curMonster->getPositionX();
								if (delat_y > 0)
									dstY = curMonster->getAttackRange() + curMonster->getPositionY();
								else
									dstY = -(curMonster->getAttackRange()) + curMonster->getPositionY();
							}
							if (dstX >= Xmin && dstX <= Xmax && dstY >= Ymin && dstY <= Ymax)
							{
								curMonster->canattack = true;
								Vec2 target = curheropos - curMonster->getPosition();
								target.normalize();
								target = target * curMonster->getAttackRange();
								auto moveby = MoveBy::create(1.0f, target);
								curMonster->runAction(moveby);
								int delta_x = target.x;
								if (delta_x < 0)
									curMonster->getSprite()->setFlippedX(true);
								else if (delta_x > 0)
									curMonster->getSprite()->setFlippedX(false);
								else
									;
								curMonster->getSprite()->runAction(curMonster->mons_Frame_animation());
							}
						}
						else
							curMonster->canattack = false;
					}
				}
				if (curMonsterType == 1|| curMonsterType == 3)
				{
					Vec2 enemyPos = curMonster->getPosition();
					if (!Hero->isdead())
					{
						if (enemyPos.distance(curheropos) < curMonster->getAttackRange())
						{
							curMonster->canattack = true;
							Vec2 target1 = curheropos - curMonster->getPosition();
							int delta_x = target1.x;
							if (delta_x < 0)
								curMonster->getSprite()->setFlippedX(true);
							else if (delta_x > 0)
								curMonster->getSprite()->setFlippedX(false);
							else
								;
							if (curMonsterType == 1)
							{
								auto arrow = Sprite::create("Bullet//bullet2.png");
								PhysicsBody* arrowbody = PhysicsBody::createBox(arrow->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
								arrowbody->setGravityEnable(false);
								arrowbody->setDynamic(false);
								arrowbody->setCategoryBitmask(0x0001);
								arrowbody->setCollisionBitmask(0x0001);
								arrowbody->setContactTestBitmask(0x0001);
								arrow->addComponent(arrowbody);
								arrow->setTag(4);
								int set_x = curMonster->getContentSize().width / 2;
								int set_y = curMonster->getContentSize().height / 2;
								arrow->setPosition(curMonster->getPositionX(), curMonster->getPositionY());
								Hero->getCurBattleRoom()->addChild(arrow);
								Vec2 target = curheropos - curMonster->getPosition();
								target.normalize();
								target = target * curMonster->getAttackRange();
								auto moveby = MoveBy::create(2.0f, target);
								auto actionRemove = RemoveSelf::create();
								arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
								curMonster->getSprite()->runAction(curMonster->mons_Frame_animation());
							}
							else
							{
								auto arrow = Sprite::create("Bullet//bullet_3.png");
								PhysicsBody* arrowbody = PhysicsBody::createBox(arrow->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
								arrowbody->setGravityEnable(false);
								arrowbody->setDynamic(false);
								arrowbody->setCategoryBitmask(0x0001);
								arrowbody->setCollisionBitmask(0x0001);
								arrowbody->setContactTestBitmask(0x0001);
								arrow->addComponent(arrowbody);
								arrow->setTag(4);
								int set_x = curMonster->getContentSize().width / 2;
								int set_y = curMonster->getContentSize().height / 2;
								arrow->setPosition(curMonster->getPositionX(), curMonster->getPositionY());
								Hero->getCurBattleRoom()->addChild(arrow);
								Vec2 target = curheropos - curMonster->getPosition();
								target.normalize();
								target = target * curMonster->getAttackRange();
								auto moveby = MoveBy::create(2.0f, target);
								auto actionRemove = RemoveSelf::create();
								arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
								curMonster->getSprite()->runAction(curMonster->mons_Frame_animation());
							}
							
						}
						else
							curMonster->canattack = false;
					}
				}
			}
		}
	}
	boss* nearboss = nullptr;
	if (this->Hero->getCurBattleRoom() != nullptr)
	{
		for (boss* curBoss : this->Hero->getCurBattleRoom()->getVecBoss())
		{
			if (!curBoss->isdead())
			{
				int curBossType = curBoss->gettype();
				if (curBossType == 0)
				{
					if (!Hero->isdead())
					{
						Vec2 enemyPos = curBoss->getPosition();
						if (enemyPos.distance(curheropos) < curBoss->getAttackRange())
						{
							//判定不会冲出房间时野猪发动冲撞
							float Xmin = curBoss->getAtBattleRoom()->getTopLeftCornerPositionX();
							float Ymin = curBoss->getAtBattleRoom()->getLowerRightCornerPositionY();
							float Xmax = curBoss->getAtBattleRoom()->getLowerRightCornerPositionX();
							float Ymax = curBoss->getAtBattleRoom()->getTopLeftCornerPositionY();

							float dstX;
							float dstY;
							float delat_x = Hero->getPositionX() - curBoss->getPositionX();
							float delat_y = Hero->getPositionY() - curBoss->getPositionY();

							int boom_chance = rand() % 3;

							if (delat_x != 0)
							{
								float tan = abs(delat_y / delat_x);
								float t_2 = tan * tan;
								float squr = 1 + t_2;
								float length = sqrt(squr);
								if (delat_x > 0)
								{
									if (boom_chance == 1)
										dstX = 600 / length;
									else
										dstX = 400 / length;
								}
								else
								{
									if (boom_chance == 1)
										dstX = -600 / length;
									else
										dstX = -400 / length;
								}
								if (delat_y > 0)
								{
									if (boom_chance == 1)
										dstY = (600 / length) * tan;
									else
										dstY = (400 / length) * tan;
								}
								else
								{
									if (boom_chance == 1)
										dstY = (-600 / length) * tan;
									else
										dstY = (-400 / length) * tan;
								}
								dstX = dstX + curBoss->getPositionX();
								dstY = dstY + curBoss->getPositionY();
							}
							else
							{
								dstX = curBoss->getPositionX();
								if (delat_y > 0)
								{
									if (boom_chance == 1)
										dstY = 600 + curBoss->getPositionY();
									else
										dstY = 400 + curBoss->getPositionY();
								}
								else
								{
									if (boom_chance == 1)
										dstY = -600 + curBoss->getPositionY();
									else
										dstY = -400 + curBoss->getPositionY();
								}
							}
							if (dstX >= Xmin && dstX <= Xmax && dstY >= Ymin && dstY <= Ymax)
							{
								Vec2 target = curheropos - curBoss->getPosition();
								target.normalize();
								if (boom_chance == 1)
								{
									curBoss->getSprite()->setScale(1.8);
									target = target * 500;
									auto moveby = MoveBy::create(0.3f, target);
									curBoss->runAction(moveby);
								}
								else
								{
									curBoss->getSprite()->setScale(1.0);
									target = target * 400;
									auto moveby = MoveBy::create(1.0f, target);
									curBoss->runAction(moveby);
								}
								int delta_x = target.x;
								if (delta_x < 0)
									curBoss->getSprite()->setFlippedX(true);
								else if (delta_x > 0)
									curBoss->getSprite()->setFlippedX(false);
								else
									;
								curBoss->getSprite()->runAction(curBoss->boss_Frame_animation());
							}
						}
					}
				}
				if (curBossType == 1)
				{
					Vec2 enemyPos = curBoss->getPosition();
					if (!Hero->isdead())
					{
						if (enemyPos.distance(curheropos) < curBoss->getAttackRange())
						{
							Vec2 target1 = curheropos - curBoss->getPosition();
							int boom_chance = rand() % 3;
							int delta_x = target1.x;
							if (delta_x < 0)
								curBoss->getSprite()->setFlippedX(true);
							else if (delta_x > 0)
								curBoss->getSprite()->setFlippedX(false);
							else
								;
							int set_x = curBoss->getContentSize().width / 2;
							int set_y = curBoss->getContentSize().height / 2;
							if (boom_chance != 1)
							{
								auto arrow = Sprite::create("Bullet//fire.png");
								PhysicsBody* arrowbody = PhysicsBody::createBox(arrow->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
								arrowbody->setGravityEnable(false);
								arrowbody->setDynamic(false);
								arrowbody->setCategoryBitmask(0x0001);
								arrowbody->setCollisionBitmask(0x0001);
								arrowbody->setContactTestBitmask(0x0001);
								arrow->addComponent(arrowbody);
								arrow->setTag(10);
								arrow->setPosition(curBoss->getPositionX(), curBoss->getPositionY());
								Hero->getCurBattleRoom()->addChild(arrow);
								Vec2 target = curheropos - curBoss->getPosition();
								target.normalize();
								target = target * 600;
								auto moveby = MoveBy::create(1.0f, target);
								auto actionRemove = RemoveSelf::create();
								arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
							}
							else
							{
								float pi = 3.1415926;
								float sita = pi / 180;
								for (int i = 1; i < 25; i++)
								{
									auto arrow = Sprite::create("Bullet//fire.png");
									PhysicsBody* arrowbody = PhysicsBody::createBox(arrow->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
									arrowbody->setGravityEnable(false);
									arrowbody->setDynamic(false);
									arrowbody->setCategoryBitmask(0x0001);
									arrowbody->setCollisionBitmask(0x0001);
									arrowbody->setContactTestBitmask(0x0001);
									arrow->addComponent(arrowbody);
									arrow->setTag(10);
									arrow->setPosition(curBoss->getPositionX(), curBoss->getPositionY());
									Hero->getCurBattleRoom()->addChild(arrow);
									if (i < 6)
									{
										float y = tan(15 * sita * i);
										Vec2 target = Vec2(1.0, y);
										target.normalize();
										target = target * 600;
										auto moveby = MoveBy::create(1.0f, target);
										auto actionRemove = RemoveSelf::create();
										arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
										//CCLOG("Y %f", y);
									}
									else if (i == 6)
									{
										Vec2 target = Vec2(0, 600);
										auto moveby = MoveBy::create(1.0f, target);
										auto actionRemove = RemoveSelf::create();
										arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
									}
									else if (i > 6 && i <= 12)
									{
										float y = abs(tan(15 * sita * i));
										Vec2 target = Vec2(-1.0, y);
										target.normalize();
										target = target * 600;
										auto moveby = MoveBy::create(1.0f, target);
										auto actionRemove = RemoveSelf::create();
										arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
										//CCLOG("Y %f", y);
									}
									else if (i > 12 && i < 18)
									{
										float y = abs(tan(15 * sita * i));
										Vec2 target = Vec2(-1.0, -y);
										target.normalize();
										target = target * 600;
										auto moveby = MoveBy::create(1.0f, target);
										auto actionRemove = RemoveSelf::create();
										arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
										//CCLOG("Y %f", y);
									}
									else if (i == 18)
									{
										Vec2 target = Vec2(0, -600);
										auto moveby = MoveBy::create(1.0f, target);
										auto actionRemove = RemoveSelf::create();
										arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
									}
									else if (i > 18 && i <= 24)
									{
										float y = abs(tan(15 * sita * i));
										Vec2 target = Vec2(1.0, -y);
										target.normalize();
										target = target * 600;
										auto moveby = MoveBy::create(1.0f, target);
										auto actionRemove = RemoveSelf::create();
										arrow->runAction(Sequence::create(moveby, actionRemove, nullptr));
										//CCLOG("Y %f", y);
									}
									else
										;
								}
							}
							curBoss->getSprite()->runAction(curBoss->boss_Frame_animation());
						}
					}
				}
			}
		}
	}
}

void battleScene::updateBattleRoomDoorState()
{
	auto curBattleRoom = Hero->getCurBattleRoom();
	if (curBattleRoom != nullptr && curBattleRoom->getBattleRoomType() == TypeNormal)
	{
		if (curBattleRoom->getIsClearance())
			curBattleRoom->setDoorOpened();
		else
			curBattleRoom->setDoorClosed();
	}
}

void battleScene::updatePortalJudgement()
{
	if (Hero->getIsFinished())
	{
		Hero->setIsFinished(false);
		battleScene::Hero->retain();
		battleScene::Hero->removeFromParent();        //从该场景移除
		battleScene::_battleSceneNumber++;            //关卡编号+1

		int num = battleScene::_battleSceneNumber;
		num = num % 5 == 0 ? num / 5 : num / 5 + 1;
		if (_battleSceneNumber - 1 == 5)
		{
			this->cleanup();
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, secureRoom::createScene()));
		}
		//if (num % vecSceneType.size() == 1 && num != 1) { //每过size关再随机打乱一次
		//	srand(static_cast<unsigned int>(time(nullptr)));
		//	std::random_shuffle(BattleScene::vecSceneType.begin(),
		//		BattleScene::vecSceneType.end());
		//}
		else
		{
			assert(battleScene::Hero->getParent() == nullptr);
			battleScene::_heroStateType = this->Hero->getHeroType();
			battleScene::_heroStateHP = this->Hero->getHP();
			battleScene::_heroStateMP = this->Hero->getMP();
			battleScene::_heroStateArmor = this->Hero->getArmor();
			battleScene::_heroStateCoin = this->Hero->getCoin();
			battleScene::_heroStateCurWeaponType = this->Hero->getCurWeapon()->getWeaponType();
			battleScene::_heroStateSecondaryWeaponType = this->Hero->getSecondaryWeaponType();
			this->cleanup();
			this->removeAllChildren();           //释放
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, battleScene::createBattleScene()));
		}

	}
}

void battleScene::updateGameLose()
{
	if (Hero->getHP() <= 0)
	{
		this->cleanup();

		auto blink = Blink::create(2.0f, 3);
		auto fadeOut = FadeOut::create(2.0f);

		auto callFunc = CallFunc::create([&]() {
			Hero->removeFromParent();
			Director::getInstance()->replaceScene(
				TransitionFade::create(2.0f, loseScene::createScene()));
			});

		Hero->runAction(Sequence::create(callFunc, NULL));

	}
}

void battleScene::updateHeroArmor(float delta)
{
	if (_recoveryCoolingTime <= 2)
		_recoveryCoolingTime++;
	else
		if (Hero->getArmor() < Hero->getMaxArmor())
			Hero->setArmor(Hero->getArmor() + 1);
	//CCLOG("Ar:%d", Hero->getArmor());
	CCLOG("CO:%d", Hero->getCoin());
}

void battleScene::updateBossState()
{
	static bool isAdded = false;
	auto curBattleRoom = Hero->getCurBattleRoom();
	if(!isAdded)
		if (curBattleRoom != nullptr && curBattleRoom->getBattleRoomType() == TypeBoss)
		{
			if (curBattleRoom->getIsClearance())
			{
				if (curBattleRoom->getIsClearance())
				{
					auto visibleSize = Director::getInstance()->getVisibleSize();
					Sprite* portal = Sprite::create("Map//portal3.png");
					auto Congratulations = Sprite::create("Congratulations.png");
					Congratulations->setPosition(visibleSize.width / 2, visibleSize.height / 4 * 3);
					portal->setPosition(Point(curBattleRoom->_centerX, curBattleRoom->_centerY));
					curBattleRoom->addChild(portal);
					portal->setGlobalZOrder(-1);
					this->addChild(Congratulations, 5);
					curBattleRoom->_portal = portal;
					isAdded = true;
				}

			}
		}
}

void battleScene::updateSkillCooling(float delta)
{
	if (_skillCoolingTime <= 4)
		_skillCoolingTime++;
}

void battleScene::nextRoomGenerate(int column, int row, battleRoom* curRoom, std::queue<battleRoom*>& roomQueue)
{
	//随关卡数增加增加房间的额外关卡机制，后续更新
	int additionalRoom = 0;
	//if (_battleSceneNumber % 5 != 1 && _battleSceneNumber % 5 != 2) 
	//{
	//	int temp = _battleSceneNumber % 5 ? _battleSceneNumber % 5 : 4;
	//	additionalRoom = temp - 2;
	//} 

	if (countForRoom >= MaxRoom + additionalRoom) 
		return;

	srand(static_cast<unsigned int>(time(nullptr)));

	std::vector<int> vecDirection;

	for (int direction = 0; direction < 4; direction++) 
	{
		if (curRoom->_visDirection[direction]) 
			continue;

		int toX = column + DirectionX[direction], toY = row + DirectionY[direction];
		if (toX < 0 || toX >= NumRoomX || toY < 0 || toY >= NumRoomY) 
			continue;

		//if (curRoom == beginRoom &&((curRoom->y < 2 && dir == DOWN) || (curRoom->y > 2 && dir == UP)))
		//	continue;

		vecDirection.push_back(direction);            //联通的方向
	}

	if (vecDirection.empty()) 
		return;

	int countDirectionChosen = std::max(2U, (rand() % (vecDirection.size() + 1U)));

	//在可行方向中随机选取所需数目方向
	for (int i = 0; i < countDirectionChosen; i++) {
		int directionIndex = rand() % vecDirection.size();
		int dir = vecDirection.at(directionIndex);
		vecDirection.erase(vecDirection.begin() + directionIndex);
		int toX = column + DirectionX[dir], toY = row + DirectionY[dir];

		if (_battleRoomMatrix[toX][toY] == _beginRoom)
			return;

		battleRoom*& nextRoom = _battleRoomMatrix[toX][toY];  
		if (battleRoom::createBattleRoom(nextRoom, curRoom, dir, toX, toY))
		{
			this->addChild(nextRoom);
			roomQueue.push(nextRoom);
			_endRoom = nextRoom;
			countForRoom++;
		}

		assert(_battleRoomMatrix[toX][toY] != nullptr);
		assert(_battleRoomMatrix[toX][toY] != _beginRoom);

		if (countForRoom >= MaxRoom || curRoom == _beginRoom || vecDirection.empty()) 
			return;
	}

}

void battleScene::beginRoomGenerate(int column, int row)
{
	//从一个房间开始向四周扩展
	Size visibleSize = Director::getInstance()->getVisibleSize();

	std::queue<battleRoom*> roomQueue;

	battleRoom*& Room = _battleRoomMatrix[column][row]; // the pointer will be changable
	Room = battleRoom::create();
	this->_beginRoom = Room;

	Room->setcolumnNum(column);
	Room->setRowNum(row);
	//log("curRoom %d %d", Room->getColumnNum(), Room->getRowNum());
	//log("beginRoom %d %d", _beginRoom->getColumnNum(), _beginRoom->getRowNum());
	Room->setCenter(visibleSize.width / 2, visibleSize.height / 2);

	this->addChild(Room, 0);

	roomQueue.push(Room);
	countForRoom++;

	while (!roomQueue.empty()) {
		battleRoom* curRoom = roomQueue.front();
		roomQueue.pop();
		// getNextRoomDirection
		nextRoomGenerate(curRoom->getColumnNum(), curRoom->getRowNum(), curRoom, roomQueue);
	}

}

void battleScene::setRoomType()
{
	Vector<battleRoom*> vecRoom;                                //用于确定特殊房间(如道具房)
	//*****************************************************meaningless**//
	int cntDirEndRoom = 0;
	for (int dir = 0; dir < 4; dir++)
		if (_endRoom->_visDirection[dir] == true)
			cntDirEndRoom++;
	//*****************************************************
	for (int y = 0; y < NumRoomY; y++) 
	{                                                           //判断房间类型并生成地图
		for (int x = 0; x < NumRoomX; x++) 
		{
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			if (curRoom == nullptr) 
				continue;
			if (curRoom == _beginRoom)
				curRoom->_battleRoomType = TypeBegin;
			else if (curRoom == _endRoom) 
			{
				if (_battleSceneNumber % 5 == 0)                //终点为boss房间
					curRoom->_battleRoomType = TypeBoss;
				else
					curRoom->_battleRoomType = TypeEnd;
			}
			else
				curRoom->_battleRoomType = TypeNormal;

			bool notConnectedToBegin = true;
			//判断一个房间是否与起点相连 相连则设为普通房间 否则待随机选择
			for (int dir = 0; dir < 4; dir++) {
				if (curRoom == _beginRoom || curRoom == _endRoom) 
				{
					notConnectedToBegin = false;
					break;
				}
				if (curRoom->_visDirection[dir] == false) 
					continue;

				battleRoom* toRoom = _battleRoomMatrix[x + DirectionX[dir]][y + DirectionY[dir]];
				if (toRoom == _beginRoom)
					notConnectedToBegin = false;      //与起始房间和终点相连
			}
			if (notConnectedToBegin) 
				vecRoom.pushBack(curRoom);
		}
	}

	//log("room size %d", vecRoom.size());
	for (int i = 0, roomIndex = 0; i < 2; i++) 
	{  
		if (vecRoom.size() == 0) 
			break;
		roomIndex = rand() % vecRoom.size();          //随机选一个房间
		battleRoom* curRoom = vecRoom.at(roomIndex);
		vecRoom.erase(vecRoom.begin() + roomIndex);

		if (i == 0)
			curRoom->_battleRoomType = TypeBox;
		else if (i == 1)
			curRoom->_battleRoomType = TypeStore;
	}
}

void battleScene::initBattleRoomGenerate()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	countForRoom = 0;

	for (int y = 0; y < NumRoomY; y++)
	{ // 25 rooms
		for (int x = 0; x < NumRoomX; x++)
		{
			_battleRoomMatrix[x][y] = nullptr;
		}
	} // 25 roomss

	srand(static_cast<unsigned int>(time(nullptr)));

	beginRoomGenerate((NumRoomX) / 2, (NumRoomY) / 2);            //在矩阵中心生成初始房间

	setRoomType();

	for (int y = 0; y < NumRoomY; y++) 
	{  // 25 rooms
		for (int x = 0; x < NumRoomX; x++) 
		{
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			if (curRoom == nullptr) continue;

			curRoom->Hero = Hero;
			curRoom->createBattleRoomMaping();
			memcpy(curRoom->_visDirectionCpy, curRoom->_visDirection, sizeof(curRoom->_visDirection));
		}
	}
}

void battleScene::setCorridorWithWidth(room* corridor,const battleRoom* fromBattleRoom,const battleRoom* toBattleRoom)
{
	corridor->_sizeX = SIZEOFCENTERDISTANCE - fromBattleRoom->_sizeX / 2 - toBattleRoom->_sizeX / 2 - 1;

	corridor->_topLeftCornerPositionX =fromBattleRoom->_centerX + WIDTHOFFLOOR * (fromBattleRoom->_sizeX / 2 + 1);
	corridor->_topLeftCornerPositionY = fromBattleRoom->_centerY + HEIGHTOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);

	corridor->_lowerRightCornerPositionX = toBattleRoom->_centerX - WIDTHOFFLOOR * (toBattleRoom->_sizeX / 2 + 1);
	corridor->_lowerRightCornerPositionY = toBattleRoom->_centerY - HEIGHTOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);
	//CCLOG("W %d,%d", corridor->_topLeftCornerPositionX, corridor->_topLeftCornerPositionY);
	corridor->createRoomMaping();
	////确定小地图绘制顶点
	//float downLeftX = miniMap->miniRoom[fromRoom->x][fromRoom->y]->upRightX;
	//float downLeftY = miniMap->miniRoom[fromRoom->x][fromRoom->y]->downLeftY + 7;
	//float upRightX = miniMap->miniRoom[toRoom->x][toRoom->y]->downLeftX;
	//float upRightY = miniMap->miniRoom[toRoom->x][toRoom->y]->upRightY - 7;
	//miniHall->drawSolidRect(Vec2(downLeftX, downLeftY), Vec2(upRightX, upRightY),
	//	Color4F(0.9f, 0.9f, 0.9f, 0.3f));
}

void battleScene::setCorridorWithHeight(room* corridor, const battleRoom* fromBattleRoom, const battleRoom* toBattleRoom)
{
	corridor->_sizeY = SIZEOFCENTERDISTANCE - fromBattleRoom->_sizeY / 2 - toBattleRoom->_sizeY / 2 - 1;

	corridor->_topLeftCornerPositionX = fromBattleRoom->_centerX - WIDTHOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);
	corridor->_topLeftCornerPositionY =fromBattleRoom->_centerY - HEIGHTOFFLOOR * (fromBattleRoom->_sizeY / 2 + 1);

	corridor->_lowerRightCornerPositionX = toBattleRoom->_centerX + WIDTHOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);
	corridor->_lowerRightCornerPositionY = toBattleRoom->_centerY + HEIGHTOFFLOOR * (toBattleRoom->_sizeY / 2 + 1);
	//CCLOG("H %d,%d", corridor->_topLeftCornerPositionX, corridor->_topLeftCornerPositionY);
	corridor->createRoomMaping();
	////确定小地图绘制顶点
	//float downLeftX = miniMap->miniRoom[toRoom->x][toRoom->y]->downLeftX + 7;
	//float downLeftY = miniMap->miniRoom[toRoom->x][toRoom->y]->upRightY;
	//float upRightX = miniMap->miniRoom[fromRoom->x][fromRoom->y]->upRightX - 7;
	//float upRightY = miniMap->miniRoom[fromRoom->x][fromRoom->y]->downLeftY;
	//miniHall->drawSolidRect(Vec2(downLeftX, downLeftY), Vec2(upRightX, upRightY),
	//	Color4F(0.9f, 0.9f, 0.9f, 0.3f));
}

void battleScene::connectRoom(battleRoom* curRoom)
{
	assert(curRoom != nullptr);

	for (int dir = 0; dir < 4; dir++) { //4 directions
		if (curRoom->_visDirectionCpy[dir] == false) 
			continue;
		int toX = curRoom->_columnNum + DirectionX[dir];
		int toY = curRoom->_rowNum + DirectionY[dir];

		auto toRoom = _battleRoomMatrix[toX][toY];
		//auto curMiniRoom = miniMap->miniRoom[curRoom->x][curRoom->y];
		//auto toMiniRoom = miniMap->miniRoom[toX][toY];

		//auto miniHall = DrawNode::create(); //生成小地图走廊
		//miniHall->setGlobalZOrder(10);

//#ifndef DEBUG
//		miniHall->setVisible(false);
//#endif  // ! 

		auto corridor = room::create(); //生成地图走廊
		corridor->Hero = Hero;
		corridor->_direction = dir;

		switch (dir) {
		case m_RIGHT:
			setCorridorWithWidth(corridor, curRoom, toRoom);
			break;
		case m_UP:
			setCorridorWithHeight(corridor, toRoom, curRoom);
			break;
		case m_LEFT:
			setCorridorWithWidth(corridor, toRoom, curRoom);
			break;
		case m_DOWN:
			setCorridorWithHeight(corridor, curRoom, toRoom);
			break;
		}

		this->addChild(corridor);
		//miniMap->addChild(miniHall);
		vecCorridor.pushBack(corridor);

		curRoom->_visDirectionCpy[dir] = false;  //标记不能来回连接
		//curMiniRoom->miniHall[dir] = miniHall;
		toRoom->_visDirectionCpy[(dir + 2) % 4] = false;  //标记不能来回连接
		//toMiniRoom->miniHall[(dir + 2) % CNTDIR] = miniHall;

		connectRoom(toRoom);
		// need to fix vis
	}

}

void battleScene::menuCloseCallbackEnd(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, initScene::createScene()));
}
//
/*进入设置面板*/
void battleScene::menuCloseCallbackSet(Ref* pSender)
{
	Scheduler* continueScheduler = Director::getInstance()->getScheduler();
	continueScheduler->pauseTarget(this);
	Director::getInstance()->pushScene(
		TransitionFade::create(1.0f, settingScene::createScene()));
	continueScheduler->resumeTarget(this);
}

void battleScene::randomBGM()
{
	srand((unsigned)time(NULL));
	int bgm_rand = rand() % 9;
	BGM;
	switch (bgm_rand) {
	case 0:
		BGM = AudioEngine::play2d("BGM/bgm_1High.mp3", true);
		break;
	case 1:
		BGM = AudioEngine::play2d("BGM/bgm_1Low.mp3", true);
		break;
	case 2:
		BGM = AudioEngine::play2d("BGM/bgm_2High.mp3", true);
		break;
	case 3:
		BGM = AudioEngine::play2d("BGM/bgm_2Low.mp3", true);
		break;
	case 4:
		BGM = AudioEngine::play2d("BGM/bgm_3High.mp3", true);
		break;
	case 5:
		BGM = AudioEngine::play2d("BGM/bgm_3Low.mp3", true);
		break;
	case 6:
		BGM = AudioEngine::play2d("BGM/bgm_4Low.mp3", true);
		break;
	case 7:
		BGM = AudioEngine::play2d("BGM/bgm_5Low.mp3", true);
		break;
	case 8:
		BGM = AudioEngine::play2d("BGM/bgm_6Low.mp3", true);
		break;
	}
}


/*升高音量*/
void battleScene::menuCloseCallbackVolumeUp(Ref* pSender) {
	auto volume = AudioEngine::getVolume(BGM);
	/*修改音量*/
	AudioEngine::setVolume(BGM, volume + 0.05f);

}

/*降低音量*/
void battleScene::menuCloseCallbackVolumeDown(Ref* pSender) {
	auto volume = AudioEngine::getVolume(BGM);
	/*修改音量*/
	AudioEngine::setVolume(BGM, volume - 0.05f);

}