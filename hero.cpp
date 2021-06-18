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

void hero::bindWeapon(weapon* weapon)
{
	this->_curWeapon = weapon;
	Size herosize = this->getContentSize();
	float weapon_x = herosize.width / 2;
	float weapon_y = herosize.height/ 2;
	this->_curWeapon->setPosition((weapon_x), (weapon_y));
	this->addChild(_curWeapon);
}

weapon* hero::getCurWeapon()
{
	return this->_curWeapon;
}

weapon* hero::getSecondaryWeapon()
{
	return this->_secondaryWeapon;
}

int hero::getWeaponType()const
{
	return this->_curWeapon->getWeaponType();
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
	if (this->getHeroType() == 1)
	{
		this->_curWeapon = nullptr;
		this->_secondaryWeapon = nullptr;
		this->_moveSpeed = 5;
		this->_heroSpeedX = 5;
		this->_heroSpeedY = 5;
		this->setMaxArmor(10);
		this->setArmor(10);
		this->setMaxHP(10);
		this->setHP(10);
		this->_canAttack = true;
		auto spritehero = Sprite::create("Character//knight1.png");
		bindSprite(spritehero);
	}
	if (this->getHeroType() == 2)
	{
		this->_curWeapon = nullptr;
		this->_secondaryWeapon = nullptr;
		this->_moveSpeed = 8;
		this->_heroSpeedX = 8;
		this->_heroSpeedY = 8;
		this->setMaxArmor(20);
		this->setArmor(20);
		this->setMaxHP(20);
		this->setHP(20);
		this->_canAttack = true;
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
				if (!(curBattleRoom->checkPortalPosition(this)))
				{
					auto curDrop = curBattleRoom->checkNearbyDrop(this);
					if (curDrop != nullptr)
						if (!curDrop->getIsUsed())
						{
							getdamage(-2);
							curDrop->setIsUsed(1);
						}
					if (curBattleRoom->getBattleRoomType() == TypeNormal)
					{
						monster* nearMonster = nullptr;
						Vec2 curPos = this->getPosition();
						float distance = 99999;
						int set_x = this->getContentSize().width / 2;
						int set_y = this->getContentSize().height / 2;

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
							if (this->getWeaponType() == 0)
							{
								if (distance < this->getCurWeapon()->getattackRange()&&_canAttack)
								{
									auto Bullet = bullet::create();
									PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
									bulletbody->setGravityEnable(false);
									bulletbody->setDynamic(false);
									bulletbody->setCategoryBitmask(0x0001);
									bulletbody->setCollisionBitmask(0x0001);
									bulletbody->setContactTestBitmask(0x0001);
									Bullet->addComponent(bulletbody);
									Bullet->setTag(3);
									Bullet->setPosition(set_x, set_y);
									this->addChild(Bullet);
									Vec2 target = nearMonster->getPosition() - curPos;
									//实现发射速度不同，可改
									auto moveby = MoveBy::create(0.7f, target * 2);
									auto actionRemove = RemoveSelf::create();
									Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
								}
							}
							if (this->getWeaponType() == 1)
							{
								this->getCurWeapon()->getSprite()->runAction(this->getCurWeapon()->wea_Frame_animation());
								for (monster* curMonster : this->getCurBattleRoom()->getVecMonster())
								{
									if (!curMonster->isdead())
									{
										Vec2 enemyPos = curMonster->getPosition();
										if (enemyPos.distance(curPos) < this->getCurWeapon()->getattackRange())
										{
											curMonster->getdamage(this->getCurWeapon()->getdamage());
										}
									}
								}
							}
						}
					}
				}
				if (curBattleRoom->getBattleRoomType() == TypeBox)
				{
					if (curBattleRoom->getChestState() == CLOSED)
					{
						curBattleRoom->openChest(this);
						curBattleRoom->setChestState(OPENED);
					}
				}
				this->_canAttack = false;
			}
			if (!keyMap[shoot])
				this->_canAttack = true;
		}

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