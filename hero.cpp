#include "hero.h"

hero::~hero() {}

bool hero::initMemHero(const std::string& fileName, float heroSpeed, int attack, int maxHP , float movingSpeed )
{
	_heroSpeed = heroSpeed;
	return(initSpriteWithFileName(fileName) && initMember(attack, maxHP, movingSpeed));
}
bool hero::init()
{
	updateKeyboardEvent();
	this->scheduleUpdate();
	/*auto listener1 = EventListenerKeyboard::create();
	listener1->onKeyPressed = [=](EventKeyboard::KeyCode Keycode, Event* event) {
		keyMap[Keycode] = true;
	};
	listener1->onKeyReleased = [=](EventKeyboard::KeyCode Keycode, Event* event) {
		keyMap[Keycode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	this->scheduleUpdate();*/
	//吴总说不太行
	return true;
}

void hero::move() {
    ;
 }
void hero::attack() {
    ;
}

void hero::updateKeyboardEvent() {
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = [=](EventKeyboard::KeyCode Keycode, Event* event) {
		keyMap[Keycode] = true;
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode Keycode, Event* event) {
		keyMap[Keycode] = false;
	};

	auto right = EventKeyboard::KeyCode::KEY_D;
	auto left = EventKeyboard::KeyCode::KEY_A;
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto down = EventKeyboard::KeyCode::KEY_S;

	if (keyMap[right])
	{
		getSprite()->setFlippedX(false);
		this->getSprite()->setPosition(getSprite()->getPositionX() + 10, getSprite()->getPositionY());
	}

	if (keyMap[left])
	{
		getSprite()->setFlippedX(true);
		this->getSprite()->setPosition(getSprite()->getPositionX() - 10, getSprite()->getPositionY());
	}

	if (keyMap[up])
	{
		this->getSprite()->setPosition(getSprite()->getPositionX(), getSprite()->getPositionY() + 10);
	}

	if (keyMap[down])
	{
		this->getSprite()->setPosition(getSprite()->getPositionX(), getSprite()->getPositionY() - 10);
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);



	/*listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event*) {
		static Vec2 last;
		static bool isRight = true;
		if (code != EventKeyboard::KeyCode::KEY_D &&
			code != EventKeyboard::KeyCode::KEY_W &&
			code != EventKeyboard::KeyCode::KEY_A &&
			code != EventKeyboard::KeyCode::KEY_S &&
			code != EventKeyboard::KeyCode::KEY_J &&
			code != EventKeyboard::KeyCode::KEY_K)
			last.set(1.0, 0);

		switch (code) {
		case EventKeyboard::KeyCode::KEY_D:
			last.set(1.0, 0);
			isRight = true;
			moveSpeedX = moveSpeed;
			getSprite()->setFlippedX(false);
			weapon->getSprite()->setFlippedX(false);
			if (!isAnimation) {
				getSprite()->runAction(getAnimate());
				isAnimation = true;
			}
			break;

		case EventKeyboard::KeyCode::KEY_W:
			last.set(0, 1.0);
			moveSpeedY = moveSpeed;
			if (!isAnimation) {
				getSprite()->runAction(getAnimate());  //执行帧动作
				isAnimation = true;
			}
			break;

		case EventKeyboard::KeyCode::KEY_A:
			isRight = false;
			last.set(-1.0, 0);
			moveSpeedX = -moveSpeed;
			getSprite()->setFlippedX(true);
			weapon->getSprite()->setFlippedX(true);
			if (!isAnimation) {
				getSprite()->runAction(getAnimate());
				isAnimation = true;
			}
			break;

		case EventKeyboard::KeyCode::KEY_S:
			last.set(0, -1.0);
			moveSpeedY = -moveSpeed;
			if (!isAnimation) {
				getSprite()->runAction(getAnimate());
				isAnimation = true;
			}
			break;

		case EventKeyboard::KeyCode::KEY_J:
			if (this->atHall == nullptr && this->atBattleRoom == nullptr) break;

			if (checkPortal()) break;
			if (checkStatue()) break;

			if (this->atBattleRoom != nullptr) {
				Weapon* weaponCheck = this->collisionWithWeaponCheck();
				Prop* prop = this->collisionWithCropCheck();
				Sprite* box = this->collisionWithBoxCheck();
				Enemy* enemy = this->collisionWithEnemyCheck();
				Boss* boss = this->collisionWithBossCheck();
				if (weaponCheck != nullptr) {
					this->bindWeapon(weaponCheck);
					if (isRight == false) weapon->getSprite()->setFlippedX(true);
					break;
				}
				else if (prop != nullptr) {
					prop->useProps(this);
					prop->removeFromParent();
					this->atBattleRoom->getVecProps().eraseObject(prop);
					break;
				}
				else if (box != nullptr) {
					this->getAtBattleRoom()->openTreasureBox();
					box->removeFromParent();
					this->atBattleRoom->getVecBox().eraseObject(box);
					break;
				}
				else if (enemy != nullptr)
					enemy->deductHP(5);
				else if (boss != nullptr)
					boss->deductHP(10);
			}
			weaponAttack(last);
			break;

		case EventKeyboard::KeyCode::KEY_K:
			if (this->atHall == nullptr && this->atBattleRoom == nullptr) break;
			useUltimateSkill();
			break;
		}
	};

	listener->onKeyReleased = [&](EventKeyboard::KeyCode code, Event*) {
		switch (code) {
		case EventKeyboard::KeyCode::KEY_D:
			moveSpeedX = .0f;
			getSprite()->stopAllActions();  //停止帧动画动作
			isAnimation = false;
			break;

		case EventKeyboard::KeyCode::KEY_W:
			moveSpeedY = .0f;
			getSprite()->stopAllActions();
			isAnimation = false;
			break;

		case EventKeyboard::KeyCode::KEY_A:
			moveSpeedX = .0f;
			getSprite()->stopAllActions();
			isAnimation = false;
			break;

		case EventKeyboard::KeyCode::KEY_S:
			moveSpeedY = .0f;
			getSprite()->stopAllActions();
			isAnimation = false;
			break;
		}
	};
*/
}
