#include "hero.h"
#include "battleRoom.h"

hero::~hero() {}

void hero::setHeroType(int type)
{
	this->_heroType = type;
}

int hero::getHeroType()const
{
	return this->_heroType;
}

void hero::bindWeapon()
{
	auto tempWeapon = weapon::create();
	auto tempSecondaryWeapon = weapon::create();
	auto tempThirdWeapon = weapon::create();
	auto tempFourthWeapon = weapon::create();
	auto tempFifthWeapon = weapon::create();

	tempWeapon->changeWeapon(0);
	tempSecondaryWeapon->changeWeapon(1);
	tempThirdWeapon->changeWeapon(2);
	tempFourthWeapon->changeWeapon(3);
	tempFifthWeapon->changeWeapon(4);


	this->_curWeapon = tempWeapon;
	this->_secondaryWeapon = tempSecondaryWeapon;
	this->_thirdWeapon = tempThirdWeapon;
	this->_fourthWeapon = tempFourthWeapon;
	this->_fifthWeapon = tempFifthWeapon;

	Size herosize = this->getContentSize();
	float weapon_x = herosize.width / 2;
	float weapon_y = herosize.height/ 2;
	this->_curWeapon->setPosition((weapon_x), (weapon_y));
	this->_secondaryWeapon->setPosition((weapon_x), (weapon_y));
	this->_thirdWeapon->setPosition((weapon_x), (weapon_y));
	this->_fourthWeapon->setPosition((weapon_x), (weapon_y));
	this->_fifthWeapon->setPosition((weapon_x), (weapon_y));

	this->addChild(_curWeapon);
	this->addChild(_secondaryWeapon);
	this->addChild(_thirdWeapon);
	this->addChild(_fourthWeapon);
	this->addChild(_fifthWeapon);

	updateWeaponDisplayStatus();
}

weapon* hero::getCurWeapon()
{
	if (0 == _curWeaponType)
		return this->_curWeapon;
	else if (1 == _curWeaponType)
		return this->_secondaryWeapon;
	else if (2 == _curWeaponType)
		return this->_thirdWeapon;
	else if (3 == _curWeaponType)
		return this->_fourthWeapon;
	else if (4 == _curWeaponType)
		return this->_fifthWeapon;
}

int hero::getWeaponType()
{
	return this->getCurWeapon()->getWeaponType();
}

Animate* hero::Frame_animation_rest() {
	auto hero_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->getHeroType() == 1)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Character//knight%d.png", i);
			hero_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}
	if (this->getHeroType() == 2)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Player2//ranger_rest%d.png", i);
			hero_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	hero_frame_animation->setDelayPerUnit(0.1f);

	hero_frame_animation->setLoops(1);

	hero_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(hero_frame_animation);

	return animate;
}


Animate* hero::Frame_animation_attack() {
	auto hero_frame_animation = Animation::create();

	char namesize[100] = { 0 };

	if (this->getHeroType() == 1)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Player1//knight_move%d.png", i);
			hero_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}
	if (this->getHeroType() == 2)
	{
		for (int i = 1; i < 5; i++)
		{
			sprintf(namesize, "Player2//ranger_move%d.png", i);
			hero_frame_animation->addSpriteFrameWithFile(namesize);
		}
	}

	hero_frame_animation->setDelayPerUnit(0.1f);

	hero_frame_animation->setLoops(1);

	hero_frame_animation->setRestoreOriginalFrame(true);

	auto animate = Animate::create(hero_frame_animation);

	return animate;
}


//绑定场景，用于读取场景里的东西
void hero::bindscene(Scene* scene) {
	_scene = scene;
}

void hero::initmem()
{
	this->_curWeapon = nullptr;
	this->_secondaryWeapon = nullptr;
	this->_canAttack = true;
	this->_canChange = true;
	this->_secondaryWeaponType = -1;
	this->setCoin(100);
	if (this->getHeroType() == 1)
	{
		this->_curWeaponType = 0;
		this->_moveSpeed = 8;
		this->_heroSpeedX = 8;
		this->_heroSpeedY = 8;
		this->setMaxArmor(15);
		this->setArmor(15);
		this->setMaxHP(10);
		this->setHP(10);
		this->setMaxMP(300);
		this->setMP(300);
		auto spritehero = Sprite::create("Character//knight1.png");
		bindSprite(spritehero);
	}
	if (this->getHeroType() == 2)
	{
		this->_curWeaponType = 1;
		this->_moveSpeed = 10;
		this->_heroSpeedX = 10;
		this->_heroSpeedY = 10;
		this->setMaxArmor(15);
		this->setArmor(15);
		this->setMaxHP(10);
		this->setHP(10);
		this->setMaxMP(150);
		this->setMP(150);
		auto spritehero = Sprite::create("Player2//ranger_rest1.png");
		bindSprite(spritehero);
	}

}

bool hero::init()
{
	this->_isFinished = false;

	this->schedule(CC_SCHEDULE_SELECTOR(hero::updatekeyboard),0.01f);
	return true;
}

void hero::truekeycode(EventKeyboard::KeyCode keycode)
{
	keyMap[keycode] = true;
}

void hero::falsekeycode(EventKeyboard::KeyCode keycode)
{
	keyMap[keycode] = false;
}

void hero::updatekeyboard(float delta)
{
		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*)
		{
			if (!this->isdead())
				this->truekeycode(code);
			else
				this->falsekeycode(code);
		};

		listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
			this->falsekeycode(code);
		};

		auto right = EventKeyboard::KeyCode::KEY_D;
		auto left = EventKeyboard::KeyCode::KEY_A;
		auto up = EventKeyboard::KeyCode::KEY_W;
		auto down = EventKeyboard::KeyCode::KEY_S;
		auto shoot = EventKeyboard::KeyCode::KEY_J;
		auto change = EventKeyboard::KeyCode::KEY_K;

		auto winSize = Director::getInstance()->getVisibleSize();
		Vec2 me_size = this->getContentSize();
		int Xmin = me_size.x;
		int Ymin = me_size.y;
		int Xmax = winSize.width;
		int Ymax = winSize.height;

		int x0 = this->getPositionX();
		int y0 = this->getPositionY();


		if (this->isdead())
		{
			this->falsekeycode(right);
			this->falsekeycode(left);
			this->falsekeycode(up);
			this->falsekeycode(down);
			this->falsekeycode(shoot);
		}
		/*auto moveby1 = MoveBy::create(0.01, Vec2(_heroSpeed, 0));
		auto moveby2 = MoveBy::create(0.01, Vec2(-_heroSpeed, 0));
		auto moveby3 = MoveBy::create(0.01, Vec2(0, _heroSpeed));
		auto moveby4 = MoveBy::create(0.01, Vec2(0, -_heroSpeed));*/

		if (keyMap[right]&& !this->isdead())
		{
			this->setmovespeedX(_moveSpeed);
			int x = x0 + this->_heroSpeedX;
			int y = y0;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				this->getSprite()->setFlippedX(false);
				this->getCurWeapon()->getSprite()->setFlippedX(false);
				if (keyMap[shoot])
					this->getSprite()->runAction(Frame_animation_attack());
				else
					this->getSprite()->runAction(Frame_animation_rest());
			}
		}
		if (keyMap[left]&& !this->isdead())
		{
			this->setmovespeedX(0 - _moveSpeed);
			int x = x0 + this->_heroSpeedX;
			int y = y0;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				this->getSprite()->setFlippedX(true);
				this->getCurWeapon()->getSprite()->setFlippedX(true);
				if (keyMap[shoot])
					this->getSprite()->runAction(Frame_animation_attack());
				else
					this->getSprite()->runAction(Frame_animation_rest());
			}
		}
		if (!keyMap[left] && !keyMap[right]&& !this->isdead())
		{
			this->setmovespeedX(0);
		}

		if (keyMap[up]&& !this->isdead())
		{
			this->setmovespeedY(_moveSpeed);
			int x = x0;
			int y = y0 + this->_heroSpeedY;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				if(keyMap[shoot])
					this->getSprite()->runAction(Frame_animation_attack());
				else
					this->getSprite()->runAction(Frame_animation_rest());
			}
		}

		if (keyMap[down]&& !this->isdead())
		{
			this->setmovespeedY(0 - _moveSpeed);
			int x = x0;
			int y = y0 + this->_heroSpeedY;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				if (keyMap[shoot])
					this->getSprite()->runAction(Frame_animation_attack());
				else
					this->getSprite()->runAction(Frame_animation_rest());
			}
		}
		if (!keyMap[up] && !keyMap[down]&& !this->isdead())
		{
			this->setmovespeedY(0);
		}

		if (this->getCurBattleRoom() != nullptr)
		{
			if (keyMap[shoot])
			{
				auto curBattleRoom = this->getCurBattleRoom();
				//CCLOG("X%d,Y%d", this->getCurBattleRoom()->getColumnNum(), this->getCurBattleRoom()->getRowNum());
				if (curBattleRoom->getBattleRoomType() == TypeStore)
				{
					if (_canAttack)
					{
						auto curDrop = curBattleRoom->checkNearbyDrop(this);
						auto curWeapon = curBattleRoom->checkNearbyWeapon(this);
						if (curDrop != nullptr)
							if (!curDrop->getIsUsed() && (_coin - curDrop->getDropPrice() >= 0))
							{
								//getdamage(-2);
								curDrop->propsUsing(this);
								curDrop->setIsUsed(1);
								this->getCurBattleRoom()->getVecdrop().eraseObject(curDrop);
								this->addCoin(0 - curDrop->getDropPrice());
								curDrop->removeFromParent();
							}
						if (curWeapon != nullptr && (_coin - curWeapon->getWeaponPrice() >= 0))
						{
							pickUpWeapon(curWeapon);
							this->addCoin(0 - curWeapon->getWeaponPrice());
							curWeapon->removeFromParent();
						}
					}
				}
				if (!(curBattleRoom->checkPortalPosition(this)))
				{
					if (_canAttack)
					{
						auto curDrop = curBattleRoom->checkNearbyDrop(this);
						if (curDrop != nullptr)
							if (!curDrop->getIsUsed())
							{
								//getdamage(-2);
								curDrop->propsUsing(this);
								curDrop->setIsUsed(1);
								this->getCurBattleRoom()->getVecdrop().eraseObject(curDrop);
								curDrop->removeFromParent();
							}
					}
					if (curBattleRoom->getBattleRoomType() == TypeNormal)
					{
						monster* nearMonster = nullptr;
						Vec2 curPos = this->getPosition();
						float distance = 99999;
						int set_x = this->getPositionX();
						int set_y = this->getPositionY();

						for (monster* curMonster : this->getCurBattleRoom()->getVecMonster())
						{
							if (!curMonster->isdead())
							{
								Vec2 enemyPos = curMonster->getPosition();
								if (enemyPos.distance(curPos) < distance)
								{
									nearMonster = curMonster;
									distance = enemyPos.distance(curPos);
								}
							}
						}
						if (nearMonster != nullptr)
						{
							if (this->getWeaponType() == 0)//单发步枪
							{
								if (distance < this->getCurWeapon()->getattackRange() && _canAttack
									&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
								{
									_MP -= this->getCurWeapon()->getMPCost();
									auto Bullet = bullet::create();
									Bullet->bindWeapon(this->getCurWeapon());
									Bullet->fullcreate();
									PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
									bulletbody->setGravityEnable(false);
									bulletbody->setDynamic(false);
									bulletbody->setCategoryBitmask(0x0001);
									bulletbody->setCollisionBitmask(0x0001);
									bulletbody->setContactTestBitmask(0x0001);
									Bullet->addComponent(bulletbody);
									Bullet->setTag(3);
									Bullet->setPosition(set_x, set_y);
									this->getCurBattleRoom()->addChild(Bullet);
									Vec2 target = nearMonster->getPosition() - curPos;
									//实现发射速度不同，可改
									auto moveby = MoveBy::create(0.7f, target * 2);
									auto actionRemove = RemoveSelf::create();
									Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
								}
							}
							if (this->getWeaponType() == 1)//大剑
							{
								this->getCurWeapon()->getSprite()->runAction(this->getCurWeapon()->wea_Frame_animation());
								for (monster* curMonster : this->getCurBattleRoom()->getVecMonster())
								{
									if (!curMonster->isdead() && _canAttack)
									{
										Vec2 enemyPos = curMonster->getPosition();
										if (enemyPos.distance(curPos) < this->getCurWeapon()->getattackRange()
											&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
											curMonster->getdamage(this->getCurWeapon()->getdamage());
										if (curMonster->isdead())
											this->addCoin(rand() % 4);
									}
								}
							}
							if (this->getWeaponType() == 2)//冲锋枪
							{
								if (distance < this->getCurWeapon()->getattackRange() && (rand() % 10 == 0)
									&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
								{
									_MP -= this->getCurWeapon()->getMPCost();
									auto Bullet = bullet::create();
									Bullet->bindWeapon(this->getCurWeapon());
									Bullet->fullcreate();
									PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
									bulletbody->setGravityEnable(false);
									bulletbody->setDynamic(false);
									bulletbody->setCategoryBitmask(0x0001);
									bulletbody->setCollisionBitmask(0x0001);
									bulletbody->setContactTestBitmask(0x0001);
									Bullet->addComponent(bulletbody);
									Bullet->setTag(3);
									Bullet->setPosition(set_x, set_y);
									this->getCurBattleRoom()->addChild(Bullet);
									Vec2 target = nearMonster->getPosition() - curPos;
									//实现发射速度不同，可改
									auto moveby = MoveBy::create(0.7f, target * 2);
									auto actionRemove = RemoveSelf::create();
									Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
								}
							}
							if (this->getWeaponType() == 3)//法杖
							{
								float pi = 3.1415926;
								float sita = pi / 180;
								if (_canAttack && ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
								{
									_MP -= this->getCurWeapon()->getMPCost();
									for (int i = 1; i <= 8; i++)
									{
										auto Bullet = bullet::create();
										Bullet->bindWeapon(this->getCurWeapon());
										Bullet->fullcreate();
										PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
										bulletbody->setGravityEnable(false);
										bulletbody->setDynamic(false);
										bulletbody->setCategoryBitmask(0x0001);
										bulletbody->setCollisionBitmask(0x0001);
										bulletbody->setContactTestBitmask(0x0001);
										Bullet->addComponent(bulletbody);
										Bullet->setTag(3);
										Bullet->setPosition(set_x, set_y);
										this->getCurBattleRoom()->addChild(Bullet);
										if (i == 1)
										{
											float y = tan(45 * sita * i);
											Vec2 target = Vec2(1.0, y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 2)
										{
											Vec2 target = Vec2(0.0, this->getCurWeapon()->getattackRange());
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 3)
										{
											float y = abs(tan(45 * sita * i));
											Vec2 target = Vec2(-1.0, y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 4)
										{
											Vec2 target = Vec2(-(this->getCurWeapon()->getattackRange()), 0.0);
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 5)
										{
											float y = abs(tan(45 * sita * i));
											Vec2 target = Vec2(-1.0, -y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 6)
										{
											Vec2 target = Vec2(0.0, -(this->getCurWeapon()->getattackRange()));
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 7)
										{
											float y = abs(tan(45 * sita * i));
											Vec2 target = Vec2(1.0, -y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else
										{
											Vec2 target = Vec2(this->getCurWeapon()->getattackRange(), 0.0);
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
									}

								}
							}
							if (this->getWeaponType() == 4)//近战黄金锤
							{
								this->getCurWeapon()->getSprite()->runAction(this->getCurWeapon()->wea_Frame_animation());
								for (monster* curMonster : this->getCurBattleRoom()->getVecMonster())
								{
									if (!curMonster->isdead() && _canAttack)
									{
										Vec2 enemyPos = curMonster->getPosition();
										if (enemyPos.distance(curPos) < this->getCurWeapon()->getattackRange()
											&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
											curMonster->getdamage(this->getCurWeapon()->getdamage());
										if (curMonster->isdead())
											this->addCoin(rand() % 4);
									}
								}
							}
							//CCLOG("MP:%d", _MP);
						}
					}
					else if (curBattleRoom->getBattleRoomType() == TypeBoss)
					{
						boss* nearBoss = nullptr;
						float distance_1 = 99999;
						int set_x = this->getPositionX();
						int set_y = this->getPositionY();
						Vec2 curPos = this->getPosition();
						

						for (boss* curBoss : this->getCurBattleRoom()->getVecBoss())
						{
							if (!curBoss->isdead())
							{
								Vec2 enemyPos = curBoss->getPosition();
								if (enemyPos.distance(curPos) < distance_1)
								{
									nearBoss = curBoss;
									distance_1 = enemyPos.distance(curPos);
								}
							}
						}
						if (nearBoss != nullptr)
						{
							if (this->getWeaponType() == 0)
							{
								if (distance_1 < this->getCurWeapon()->getattackRange() && _canAttack
									&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
								{
									_MP -= this->getCurWeapon()->getMPCost();
									auto Bullet = bullet::create();
									Bullet->bindWeapon(this->getCurWeapon());
									Bullet->fullcreate();
									PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
									bulletbody->setGravityEnable(false);
									bulletbody->setDynamic(false);
									bulletbody->setCategoryBitmask(0x0001);
									bulletbody->setCollisionBitmask(0x0001);
									bulletbody->setContactTestBitmask(0x0001);
									Bullet->addComponent(bulletbody);
									Bullet->setTag(3);
									Bullet->setPosition(set_x, set_y);
									this->getCurBattleRoom()->addChild(Bullet);
									Vec2 target = nearBoss->getPosition() - curPos;
									//实现发射速度不同，可改
									auto moveby = MoveBy::create(0.7f, target * 2);
									auto actionRemove = RemoveSelf::create();
									Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
								}
							}
							if (this->getWeaponType() == 1)
							{
								this->getCurWeapon()->getSprite()->runAction(this->getCurWeapon()->wea_Frame_animation());
								for (boss* curBoss : this->getCurBattleRoom()->getVecBoss())
								{
									if (!curBoss->isdead() && _canAttack)
									{
										Vec2 enemyPos = curBoss->getPosition();
										if (enemyPos.distance(curPos) < this->getCurWeapon()->getattackRange()
											&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
											curBoss->getdamage(this->getCurWeapon()->getdamage());
										if (curBoss->isdead())
											this->addCoin(10 + rand() % 10);
									}
								}
							}
							if (this->getWeaponType() == 2)//冲锋枪
							{
								if (distance_1 < this->getCurWeapon()->getattackRange() && (rand() % 10 == 0)
									&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
								{
									_MP -= this->getCurWeapon()->getMPCost();
									auto Bullet = bullet::create();
									Bullet->bindWeapon(this->getCurWeapon());
									Bullet->fullcreate();
									PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
									bulletbody->setGravityEnable(false);
									bulletbody->setDynamic(false);
									bulletbody->setCategoryBitmask(0x0001);
									bulletbody->setCollisionBitmask(0x0001);
									bulletbody->setContactTestBitmask(0x0001);
									Bullet->addComponent(bulletbody);
									Bullet->setTag(3);
									Bullet->setPosition(set_x, set_y);
									this->getCurBattleRoom()->addChild(Bullet);
									Vec2 target = nearBoss->getPosition() - curPos;
									//实现发射速度不同，可改
									auto moveby = MoveBy::create(0.7f, target * 2);
									auto actionRemove = RemoveSelf::create();
									Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
								}
							}
							if (this->getWeaponType() == 3)//法杖
							{
								float pi = 3.1415926;
								float sita = pi / 180;
								if (_canAttack && ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
								{
									_MP -= this->getCurWeapon()->getMPCost();
									for (int i = 1; i <= 8; i++)
									{
										auto Bullet = bullet::create();
										Bullet->bindWeapon(this->getCurWeapon());
										Bullet->fullcreate();
										PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
										bulletbody->setGravityEnable(false);
										bulletbody->setDynamic(false);
										bulletbody->setCategoryBitmask(0x0001);
										bulletbody->setCollisionBitmask(0x0001);
										bulletbody->setContactTestBitmask(0x0001);
										Bullet->addComponent(bulletbody);
										Bullet->setTag(3);
										Bullet->setPosition(set_x, set_y);
										this->getCurBattleRoom()->addChild(Bullet);
										if (i == 1)
										{
											float y = tan(45 * sita * i);
											Vec2 target = Vec2(1.0, y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 2)
										{
											Vec2 target = Vec2(0.0, this->getCurWeapon()->getattackRange());
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 3)
										{
											float y = abs(tan(45 * sita * i));
											Vec2 target = Vec2(-1.0, y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 4)
										{
											Vec2 target = Vec2(-(this->getCurWeapon()->getattackRange()), 0.0);
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 5)
										{
											float y = abs(tan(45 * sita * i));
											Vec2 target = Vec2(-1.0, -y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 6)
										{
											Vec2 target = Vec2(0.0, -(this->getCurWeapon()->getattackRange()));
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else if (i == 7)
										{
											float y = abs(tan(45 * sita * i));
											Vec2 target = Vec2(1.0, -y);
											target.normalize();
											target = target * this->getCurWeapon()->getattackRange();
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
										else
										{
											Vec2 target = Vec2(this->getCurWeapon()->getattackRange(), 0.0);
											auto moveby = MoveBy::create(1.0f, target);
											auto actionRemove = RemoveSelf::create();
											Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
										}
									}

								}
							}
							if (this->getWeaponType() == 4)
							{
								this->getCurWeapon()->getSprite()->runAction(this->getCurWeapon()->wea_Frame_animation());
								for (boss* curBoss : this->getCurBattleRoom()->getVecBoss())
								{
									if (!curBoss->isdead() && _canAttack)
									{
										Vec2 enemyPos = curBoss->getPosition();
										if (enemyPos.distance(curPos) < this->getCurWeapon()->getattackRange()
											&& ((this->_MP) - (this->getCurWeapon()->getMPCost()) >= 0))
											curBoss->getdamage(this->getCurWeapon()->getdamage());
										if (curBoss->isdead())
											this->addCoin(10 + rand() % 10);
									}
								}
							}
						}
					}
				}
				if (curBattleRoom->getBattleRoomType() == TypeBox)
				{
					if (curBattleRoom->getChestState() == CLOSED)
						if (curBattleRoom->openChest(this))
							curBattleRoom->setChestState(OPENED);
				}
				this->_canAttack = false;
			}
			if (!keyMap[shoot])
			{
					this->_canAttack = true;
			}
		}
		if (keyMap[change])
		{
			if (_canChange)
				changeWeapon();
			_canChange = false;
		}
		if (!keyMap[change])
			_canChange = true;

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

int hero::getArmor() const { return this->_armor; }

void hero::setArmor(int armor) { this->_armor = std::min(armor, _armorMax); }

int hero::getMaxArmor() const { return this->_armorMax; }

void hero::setMaxArmor(int maxarmor) { this->_armorMax = maxarmor; }
	
void hero::getdamage(int damage)
{
	if (damage < 0)
	{
		if (_HP - damage <= _maxHP)
			this->_HP -= damage;
		else
		{
			this->_HP = _maxHP;
		}
	}
	else
	{
		if (_armor - damage >= 0)
			this->_armor -= damage;
		else
		{
			this->_armor = 0;
			this->_HP -= damage - _armor;
		}
	}
}

void hero::addCoin(int deltaCoin)
{
	_coin += deltaCoin;
}

void hero::setmovespeedX(float spd)
{
	this->_heroSpeedX = spd;
}
float hero::getmovespeedX() const 
{
	return this->_heroSpeedX;
}
void hero::setmovespeedY(float spd)
{
	this->_heroSpeedY = spd;
}
float hero::getmovespeedY() const
{
	return this->_heroSpeedY;
}

void hero::pickUpWeapon(weapon* pickedWeapon)
{
	if (_secondaryWeaponType < 0)
	{
		_secondaryWeaponType = _curWeaponType;
		_curWeaponType = pickedWeapon->getWeaponType();
		this->_curBattleRoom->getVecWeapon().eraseObject(pickedWeapon);
		updateWeaponDisplayStatus();
	}
	else if (_secondaryWeaponType >= 0)
	{
		auto myWeaponType = _curWeaponType;
		_curWeaponType = pickedWeapon->getWeaponType();

		weapon* myWeapon = weapon::create();
		myWeapon->changeWeapon(myWeaponType);
		myWeapon->setWeaponPrice(0);
		myWeapon->setPosition(pickedWeapon->getPosition());
		this->_curBattleRoom->addChild(myWeapon);
		this->_curBattleRoom->getVecWeapon().eraseObject(pickedWeapon);
		this->_curBattleRoom->getVecWeapon().pushBack(myWeapon);
		updateWeaponDisplayStatus();
	}
}

void hero::changeWeapon()
{
	if (_secondaryWeaponType >= 0)
	{
		auto tempWeaponType = _secondaryWeaponType;
		_secondaryWeaponType = _curWeaponType;
		_curWeaponType = tempWeaponType;
		updateWeaponDisplayStatus();
	}
}

void hero::updateWeaponDisplayStatus()
{
	if (0 != _curWeaponType)
		_curWeapon->getSprite()->setVisible(false);
	else
		_curWeapon->getSprite()->setVisible(true);
	if (1 != _curWeaponType)
		_secondaryWeapon->getSprite()->setVisible(false);
	else
		_secondaryWeapon->getSprite()->setVisible(true);
	if (2 != _curWeaponType)
		_thirdWeapon->getSprite()->setVisible(false);
	else
		_thirdWeapon->getSprite()->setVisible(true);
	if (3 != _curWeaponType)
		_fourthWeapon->getSprite()->setVisible(false);
	else
		_fourthWeapon->getSprite()->setVisible(true);
	if (4 != _curWeaponType)
		_fifthWeapon->getSprite()->setVisible(false);
	else
		_fifthWeapon->getSprite()->setVisible(true);

}