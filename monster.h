#include "cocos2d.h"
#include <vector>
#include "character.h"

USING_NS_CC;

#ifndef _MONSTER_H_
#define _MONSTER_H_

class battleRoom;

class monster : public character {
public:
	monster() = default;
	~monster();
	CREATE_FUNC(monster);

	void move(float delta);

	virtual bool init();

	void bindAtBattleRoom(battleRoom* curBattleRoom);

	bool getIsAdded() const; 

	void setIsAdded(bool); 

	battleRoom* getAtBattleRoom() const; 

	void dead();

private:
	void setAttackRange();
	int enemyType = 0;
	int ATTACKRANGE;
	bool isAdded;  
protected:
	battleRoom* atBattleRoom;
};

#endif
