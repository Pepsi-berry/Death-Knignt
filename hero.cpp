#include "hero.h"
#include "battleRoom.h"

hero::~hero() {}

Animate* hero::Frame_animation() {
	auto hero_frame_animation = Animation::create();

	char namesize[30] = { 0 };

	for (int i = 1; i < 5; i++)
	{
		sprintf(namesize, "Character//knight%d.png", i);
		hero_frame_animation->addSpriteFrameWithFile(namesize);
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

void hero::initmem(float speed, int armormax, int hpmax)
{
	this->_heroSpeedX = speed;
	this->_heroSpeedY = speed;
	this->setMaxArmor(armormax);
	this->setArmor(armormax);
	this->setMaxHP(hpmax);
	this->setHP(hpmax);
}

bool hero::init()
{
	auto spritehero = Sprite::create("Character//knight.png");
	bindSprite(spritehero);
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
			this->setmovespeedX(5);
			int x = x0 + this->_heroSpeedX;
			int y = y0;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				this->getSprite()->setFlippedX(false);
				this->getSprite()->runAction(Frame_animation());
				//this->setPosition(x, y);
			}
		}
		if (keyMap[left]&& !this->isdead())
		{
			this->setmovespeedX(-5);
			int x = x0 + this->_heroSpeedX;
			int y = y0;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				this->getSprite()->setFlippedX(true);
				this->getSprite()->runAction(Frame_animation());
				//this->setPosition(x, y);
			}
		}
		if (!keyMap[left] && !keyMap[right]&& !this->isdead())
		{
			this->setmovespeedX(0);
		}

		if (keyMap[up]&& !this->isdead())
		{
			this->setmovespeedY(5);
			int x = x0;
			int y = y0 + this->_heroSpeedY;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				this->getSprite()->runAction(Frame_animation());
				//this->setPosition(x, y);
			}
		}

		if (keyMap[down]&& !this->isdead())
		{
			this->setmovespeedY(-5);
			int x = x0;
			int y = y0 + this->_heroSpeedY;
			if (x > Xmin - 5 && x < Xmax + 5 && y>Ymin - 5 && y < Ymax + 5)
			{
				this->getSprite()->runAction(Frame_animation());
				//this->setPosition(x, y);
			}
		}
		if (!keyMap[up] && !keyMap[down]&& !this->isdead())
		{
			this->setmovespeedY(0);
		}
		//if (!keyMap[up] && !keyMap[down] && !keyMap[left] && !keyMap[right])
		//{
		//	getSprite()->stopAllActions();
		//}

		if (this->getCurBattleRoom() != nullptr)
			if (keyMap[shoot])
			{
				//CCLOG("X%d,Y%d", this->getCurBattleRoom()->getColumnNum(), this->getCurBattleRoom()->getRowNum());
				if (this->getCurBattleRoom()->getBattleRoomType() == TypeNormal)
				{
					//auto Bullet = bullet::create();
					//PhysicsBody* bulletbody = PhysicsBody::createBox(Bullet->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
					//bulletbody->setGravityEnable(false);
					//bulletbody->setDynamic(false);
					//bulletbody->setCategoryBitmask(0x0001);
					//bulletbody->setCollisionBitmask(0x0001);
					//bulletbody->setContactTestBitmask(0x0001);
					//Bullet->addComponent(bulletbody);
					//Bullet->setTag(3);
					monster* nearMonster = nullptr;
					Vec2 curPos = this->getPosition();
					float distance = 99999;
					int set_x = this->getContentSize().width / 2;
					int set_y = this->getContentSize().height / 2;
					//Bullet->setPosition(set_x, set_y);
					//this->addChild(Bullet);
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
						auto moveby = MoveBy::create(0.7f, target * 2);
						auto actionRemove = RemoveSelf::create();
						Bullet->runAction(Sequence::create(moveby, actionRemove, nullptr));
					}
					//else
					//{
					//	auto actionRemove = RemoveSelf::create();
					//	Bullet->runAction(actionRemove);
					//}
				}
			}

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

int hero::getArmor() const { return this->_armor; }

void hero::setArmor(int armor) { this->_armor = std::min(armor, _armorMax); }

int hero::getMaxArmor() const { return this->_armorMax; }

void hero::setMaxArmor(int maxarmor) { this->_armorMax = maxarmor; }
	
void hero::getdamage(int damage)
{
	this->_armor -= damage;
	if (this->_armor < 0)
		(this->_HP) += _armor;
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