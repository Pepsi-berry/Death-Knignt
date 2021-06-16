#include "cocos2d.h"
#include <vector>
#include "character.h"

USING_NS_CC;

#ifndef _ARCHER_H_
#define _ARCHER_H_

class battleRoom;

class archer : public character {
public:
	bool canattack = false;
	archer() = default;
	~archer();
	CREATE_FUNC(archer);

	void move(float delta);

	virtual bool init();

	void bindAtBattleRoom(battleRoom* curBattleRoom);

	bool getIsAdded() const;

	void setIsAdded(bool);

	battleRoom* getAtBattleRoom() const;

	void dead();

	int getmydamage()const;

private:
	int _damage = 4;
	int enemyType = 1;
	int ATTACKRANGE=800;
	bool isAdded;
protected:
	battleRoom* atBattleRoom;
};


#endif
