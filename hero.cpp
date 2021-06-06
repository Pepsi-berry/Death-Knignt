#include "hero.h"


USING_NS_CC;
bool hero::init()
{
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

void hero::update(float delta)
{
        auto right = (EventKeyboard::KeyCode)127;
        auto left = (EventKeyboard::KeyCode)124;
        auto up = (EventKeyboard::KeyCode)146;
        auto down = (EventKeyboard::KeyCode)142;
        if (keyMap[right])
        {
            setPosition(this->getPositionX() + 10, this->getPositionY());
        }

        if (keyMap[left])
        {
            setPosition(this->getPositionX() - 10, this->getPositionY());

        }
        if (keyMap[up])
        {
            setPosition(this->getPositionX(), this->getPositionY() + 10);

        }

        if (keyMap[down])
        {
            setPosition(this->getPositionX(), this->getPositionY() - 10);

        }
}