#ifndef _BATTLE_ROOM_
#define _BATTLE_ROOM_

#include "room.h"
#include "drop.h"

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
	void createBoss();
	void generateDoorMaping(float positionX, float positionY, int layer);

	void setRowNum(int rowNum) { _rowNum = rowNum; }
	void setcolumnNum(int columnNum) { _columnNum = columnNum; }
	void setIsAtBattleRoom(bool isAtBattleRoom) { _isAtBattleRoom = isAtBattleRoom; }
	void setBattleRoomType(int battleRoomType) { _battleRoomType = battleRoomType; }
	void setChestState(bool chestState) { _chestState = chestState; }

	//bool checkIsAtBattleRoom();
	void checkBattleRoomBoundaryBarrier(hero* Hero);
	bool checkPortalPosition(hero* Hero);
	Sprite* checkNearbyChest(hero* Hero);
	drop* checkNearbyDrop(hero* Hero);
	void openChest(hero* Hero);

	int getRowNum() { return _rowNum; }
	int getColumnNum() { return _columnNum; }
	//bool getIsAtBattleRoom(hero* Hero);
	int getBattleRoomType() { return _battleRoomType; }
	bool getIsClearance();
	bool getChestState() { return _chestState; }

	Vector<weapon*>& getVecWeapon() { return _vecWeapon; }
	Vector<Sprite*>& getVecBox() { return _vecBox; }
	Vector<monster*>& getVecMonster() { return _vecMonster; }
	Vector<boss*>& getVecBoss() { return _vecBoss; }
	Vector<drop*>& getVecdrop() { return _vecDrop; }

	void setDoorOpened();
	void setDoorClosed();

//protected:
//
private:
	int _battleRoomType;

	int _rowNum, _columnNum;                    //在房间矩阵中的行列序号

	bool _connectedDirection[4] = { false };    //储存房间某方向是否有与其相连的房间
	bool _visDirection[4] = { false };          //储存房间某方向是否已存在房间
	bool _visDirectionCpy[4] = { false };       

	bool _isAtBattleRoom;                       //储存游戏主角是否位于该房间
	bool _chestState;                           //储存箱子是否已被打开

	Vector<weapon*> _vecWeapon;                 //用于对生成的武器进行管理,主要在于切换武器
	Vector<Sprite*> _vecBox;                    //用于对生成在地图中的箱子进行管理,主要在于开箱子
	Vector<monster*> _vecMonster;               //储存生成在房间中的怪物实体,便于进行更新状态和射击等的功能实现
	Vector<boss*> _vecBoss;
	Vector<drop*> _vecDrop;                     //储存生成在房间中的道具,以完成拾取
	Sprite* _portal;                            //用于终点传送判定

	//实现开关战斗房间门的图像切换
	Vector<Sprite*> vecDoorOpened, vecDoorClosed;



};




#endif // !_BATTLE_ROOM_
