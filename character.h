#ifndef _CHARACTER_
#define _CHARACTER_

#include "cocos2d.h"

USING_NS_CC;

class character :public Node {
public:
	character() = default;

	Sprite* getSprite();


	virtual void showDeathEffect();
	virtual void getdamage(int damage);

	void bindSprite(Sprite* sprite, int layer);
	void setMaxHP(int maxhp);
	int getMaxHP() const;
	void setHP(int hp);
	int getHP() const;
	void setMoveSpeed(float movespeed);
	float getMoveSpeed() const;
	bool initSpriteWithFileName(const std::string& fileName);
	bool initMember(int attack = 3, int maxHP = 10, float moveSpeed = 0.0f);


	bool isdead() const;

	~character();

private:
	Sprite* _spriteInCharacter;
protected:
	int _attack = 3;
	int _HP = 10, _maxHP = 10;
	//float attackSpeed = 0.0f;  
	float _moveSpeed = 0.0f;  

};

#endif //_CHARACTER_