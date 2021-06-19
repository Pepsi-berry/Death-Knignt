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

	int _rowNum, _columnNum;                    //�ڷ�������е��������

	bool _connectedDirection[4] = { false };    //���淿��ĳ�����Ƿ������������ķ���
	bool _visDirection[4] = { false };          //���淿��ĳ�����Ƿ��Ѵ��ڷ���
	bool _visDirectionCpy[4] = { false };       

	bool _isAtBattleRoom;                       //������Ϸ�����Ƿ�λ�ڸ÷���
	bool _chestState;                           //���������Ƿ��ѱ���

	Vector<weapon*> _vecWeapon;                 //���ڶ����ɵ��������й���,��Ҫ�����л�����
	Vector<Sprite*> _vecBox;                    //���ڶ������ڵ�ͼ�е����ӽ��й���,��Ҫ���ڿ�����
	Vector<monster*> _vecMonster;               //���������ڷ����еĹ���ʵ��,���ڽ��и���״̬������ȵĹ���ʵ��
	Vector<boss*> _vecBoss;
	Vector<drop*> _vecDrop;                     //���������ڷ����еĵ���,�����ʰȡ
	Sprite* _portal;                            //�����յ㴫���ж�

	//ʵ�ֿ���ս�������ŵ�ͼ���л�
	Vector<Sprite*> vecDoorOpened, vecDoorClosed;



};




#endif // !_BATTLE_ROOM_
