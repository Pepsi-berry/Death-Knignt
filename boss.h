#include "cocos2d.h"
#include <vector>
#include "character.h"

USING_NS_CC;

#ifndef _BOSS_H_
#define _BOSS_H_

class battleRoom;

class boss : public character {
public:
	bool isattack = false;
	boss() = default;
	~boss();
	CREATE_FUNC(boss);

	void move(float delta);
	void updatedead(float delta);

	virtual bool init();

	void bindAtBattleRoom(battleRoom* curBattleRoom);

	bool getIsAdded() const;

	void setIsAdded(bool);

	battleRoom* getAtBattleRoom() const;

	int getbossdamage()const;

	void settype();
	int gettype()const;

	void setAttackRange();
	int getAttackRange()const;


	Animate* boss_Frame_animation();
	Animate* boss_Frame_animation_dead();
private:
	int _bossdamage = 5;
	int bossType;
	int ATTACKRANGE;
	bool isAdded;
protected:
	battleRoom* atBattleRoom;
};

#endif
