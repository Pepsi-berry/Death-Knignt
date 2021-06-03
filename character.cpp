#include"character.h"

USING_NS_CC;

void character::move() {
    ;
}

void character::attack() {
    ;
}

bool character::isdead()
{
    return _hp <= 0;
}
void  character::getdamage(int damage)
{
    _hp -= damage;
}