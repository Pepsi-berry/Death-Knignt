#ifndef _BATTLE_ROOM_
#define _BATTLE_ROOM_

#include "room.h"

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
	void generateDoorMaping(float positionX, float positionY, int layer);

	void setRowNum(int rowNum) { _rowNum = rowNum; }
	void setcolumnNum(int columnNum) { _columnNum = columnNum; }

	int getRowNum() { return _rowNum; }
	int getColumnNum() { return _columnNum; }

	Vector<weapon*>& getVecWeapon() { return _vecWeapon; }
	Vector<Sprite*>& getVecBox() { return _vecBox; }

//protected:
//
private:
	int _battleRoomType;

	int _rowNum, _columnNum;                    //�ڷ�������е��������

	bool _connectedDirection[4] = { false };    //���淿��ĳ�����Ƿ������������ķ���
	bool _visDirection[4] = { false };          //���淿��ĳ�����Ƿ��Ѵ��ڷ���
	bool _visDirectionCpy[4] = { false };       

	Vector<weapon*> _vecWeapon;                 //���ڶ����ɵ��������й���,��Ҫ�����л�����
	Vector<Sprite*> _vecBox;                    //���ڶ������ڵ�ͼ�е����ӽ��й���,��Ҫ���ڿ�����


};




#endif // !_BATTLE_ROOM_
