#ifndef _BATTLE_ROOM_
#define _BATTLE_ROOM_

#include "room.h"

//class monster;

USING_NS_CC;

class battleRoom : public room 
{
	friend class battleScene;
	static bool createBattleRoom(battleRoom*& toBattleRoom, battleRoom* curBattleRoom, int direction, int toX, int toY);
public:
	CREATE_FUNC(battleRoom);
	virtual bool init();
	virtual void update(float delta);


	void createBattleRoomMaping();
	void createBox(float positionX, float positionY);
	void createMonster();
	void generateDoorMaping(float positionX, float positionY, int layer);

	void setRowNum(int rowNum) { _rowNum = rowNum; }
	void setcolumnNum(int columnNum) { _columnNum = columnNum; }
	void setIsAtBattleRoom(bool isAtBattleRoom) { _isAtBattleRoom = isAtBattleRoom; }
	void setBattleRoomType(int battleRoomType) { _battleRoomType = battleRoomType; }
	//bool checkIsAtBattleRoom();
	void checkBattleRoomBoundaryBarrier(hero* Hero);

	int getRowNum() { return _rowNum; }
	int getColumnNum() { return _columnNum; }
	//bool getIsAtBattleRoom(hero* Hero);
	int getBattleRoomType() { return _battleRoomType; }

	Vector<weapon*>& getVecWeapon() { return _vecWeapon; }
	Vector<Sprite*>& getVecBox() { return _vecBox; }
	Vector<monster*>& getVecMonster() { return _vecMonster; }

//protected:
//
private:
	int _battleRoomType;

	int _rowNum, _columnNum;                    //在房间矩阵中的行列序号

	bool _connectedDirection[4] = { false };    //储存房间某方向是否有与其相连的房间
	bool _visDirection[4] = { false };          //储存房间某方向是否已存在房间
	bool _visDirectionCpy[4] = { false };       

	bool _isAtBattleRoom;                       //储存游戏主角是否位于该房间

	Vector<weapon*> _vecWeapon;                 //用于对生成的武器进行管理,主要在于切换武器
	Vector<Sprite*> _vecBox;                    //用于对生成在地图中的箱子进行管理,主要在于开箱子
	Vector<monster*> _vecMonster;               //储存生成在房间中的怪物实体,便于进行更新状态和射击等的功能实现



};




#endif // !_BATTLE_ROOM_
