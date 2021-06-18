#include "cocos2d.h"
#include <vector>
#include "character.h"

USING_NS_CC;

#ifndef _MONSTER_H_
#define _MONSTER_H_

class battleRoom;

class monster : public character {
public:
	bool canattack = false;
	monster() = default;
	~monster();
	CREATE_FUNC(monster);

	void move(float delta);
	void updatedead(float delta);

	virtual bool init();

	void bindAtBattleRoom(battleRoom* curBattleRoom);

	bool getIsAdded() const; 

	void setIsAdded(bool); 

	battleRoom* getAtBattleRoom() const; 

	void dead();

	int getmydamage()const;

	void settype();
	int gettype()const;

	void setAttackRange();
	int getAttackRange()const;


	Animate* mons_Frame_animation();
	Animate* mons_Frame_animation_rest();
	Animate* mons_Frame_animation_dead();
private:
	int _damage=2;
	int enemyType ;
	int ATTACKRANGE;
	bool isAdded;  
protected:
	battleRoom* atBattleRoom;
};

#endif
