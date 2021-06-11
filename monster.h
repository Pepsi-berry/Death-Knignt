#include"cocos2d.h"
#include <vector>
#include "character.h"

USING_NS_CC;

#ifndef _MONSTER_H_
#define _MONSTER_H_

class monster : public character {
public:
	monster() = default;
	~monster();
	CREATE_FUNC(monster);

	void move(float delta);

	virtual bool init();

	void bindAtBattleRoom(Scene* scene);

	bool getIsAdded() const; 

	void setIsAdded(bool); 

	Scene* getAtBattleRoom() const; 

private:
	void setAttackRange();
	int enemyType = 0;
	int ATTACKRANGE;
	bool isAdded;  
protected:
	Scene* atBattleRoom;
};

#endif
