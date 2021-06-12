#include "hero.h"

hero::~hero() {}

//绑定场景，用于读取场景里的东西
void hero::bindscene(Scene* scene) {
	_scene = scene;
}

bool hero::init()
{
	auto spritehero = Sprite::create("knight1.png");
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
		this->truekeycode(code);
	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		this->falsekeycode(code);
	};

	auto right = EventKeyboard::KeyCode::KEY_D;
	auto left = EventKeyboard::KeyCode::KEY_A;
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto down = EventKeyboard::KeyCode::KEY_S;

	auto winSize = Director::getInstance()->getVisibleSize();
	int std_x = winSize.width;
	int std_y = winSize.height;

	if (keyMap[right])
	{
		int x = this->getSprite()->getPositionX() + 10;
		int y = this->getSprite()->getPositionY();
		if (x > 10 && x < std_x && y>10 && y < winSize.height)
			this->getSprite()->setPosition(x, y);
	}
	if (keyMap[left])
	{
		int x = this->getSprite()->getPositionX() - 10;
		int y = this->getSprite()->getPositionY();
		if (x > 10 && x < std_x && y>10 && y < winSize.height)
			this->getSprite()->setPosition(x, y);

	}
	if (keyMap[up])
	{
		int x = this->getSprite()->getPositionX();
		int y = this->getSprite()->getPositionY() + 10;
		if (x > 10 && x < std_x && y>10 && y < winSize.height)
			this->getSprite()->setPosition(x, y);

	}
	if (keyMap[down])
	{
		int x = this->getSprite()->getPositionX();
		int y = this->getSprite()->getPositionY() - 10;
		if (x > 10 && x < std_x && y>10 && y < winSize.height)
			this->getSprite()->setPosition(x, y);

	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

	
