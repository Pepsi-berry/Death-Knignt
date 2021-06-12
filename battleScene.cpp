#include "battleScene.h"
#include "set_scene.h"

hero* battleScene::Hero = nullptr;
int battleScene::_battleSceneNumber = 0;

bool battleScene::init()
{
	if (!Scene::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	initBattleRoomGenerate(); 
	connectRoom(_beginRoom); 

	this->scheduleUpdate();
	return true;
}

void battleScene::update(float delta)
{

}

void battleScene::nextRoomGenerate(int column, int row, battleRoom* curRoom, std::queue<battleRoom*>& roomQueue)
{
	//��ؿ����������ӷ���Ķ���ؿ����ƣ���������
	int additionalRoom = 0;
	//if (_battleSceneNumber % 5 != 1 && _battleSceneNumber % 5 != 2) 
	//{
	//	int temp = _battleSceneNumber % 5 ? _battleSceneNumber % 5 : 4;
	//	additionalRoom = temp - 2;
	//} 

	if (countForRoom >= MaxRoom + additionalRoom) 
		return;

	srand(static_cast<unsigned int>(time(nullptr)));

	std::vector<int> vecDirection;

	for (int direction = 0; direction < 4; direction++) 
	{
		if (curRoom->_visDirection[direction]) 
			continue;

		int toX = column + DirectionX[direction], toY = row + DirectionY[direction];
		if (toX < 0 || toX >= NumRoomX || toY < 0 || toY >= NumRoomY) 
			continue;

		//if (curRoom == beginRoom &&((curRoom->y < 2 && dir == DOWN) || (curRoom->y > 2 && dir == UP)))
		//	continue;

		vecDirection.push_back(direction);            //��ͨ�ķ���
	}

	if (vecDirection.empty()) 
		return;

	int countDirectionChosen = std::max(2U, (rand() % (vecDirection.size() + 1U)));

	//�ڿ��з��������ѡȡ������Ŀ����
	for (int i = 0; i < countDirectionChosen; i++) {
		int directionIndex = rand() % vecDirection.size();
		int dir = vecDirection.at(directionIndex);
		vecDirection.erase(vecDirection.begin() + directionIndex);
		int toX = column + DirectionX[dir], toY = row + DirectionY[dir];

		if (_battleRoomMatrix[toX][toY] == _beginRoom)
			return;

		battleRoom*& nextRoom = _battleRoomMatrix[toX][toY];  
		if (battleRoom::createBattleRoom(nextRoom, curRoom, dir, toX, toY))
		{
			this->addChild(nextRoom);
			roomQueue.push(nextRoom);
			_endRoom = nextRoom;
			countForRoom++;
		}

		assert(_battleRoomMatrix[toX][toY] != nullptr);
		assert(_battleRoomMatrix[toX][toY] != _beginRoom);

		if (countForRoom >= MaxRoom || curRoom == _beginRoom || vecDirection.empty()) 
			return;
	}

}

void battleScene::beginRoomGenerate(int column, int row)
{
	//��һ�����俪ʼ��������չ
	Size visibleSize = Director::getInstance()->getVisibleSize();

	std::queue<battleRoom*> roomQueue;

	battleRoom*& Room = _battleRoomMatrix[column][row]; // the pointer will be changable
	Room = battleRoom::create();
	this->_beginRoom = Room;

	Room->setcolumnNum(column);
	Room->setRowNum(row);
	log("curRoom %d %d", Room->getColumnNum(), Room->getRowNum());
	log("beginRoom %d %d", _beginRoom->getColumnNum(), _beginRoom->getRowNum());
	Room->setCenter(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(Room, 0);

	roomQueue.push(Room);
	countForRoom++;

	while (!roomQueue.empty()) {
		battleRoom* curRoom = roomQueue.front();
		roomQueue.pop();
		// getNextRoomDirection
		nextRoomGenerate(curRoom->getColumnNum(), curRoom->getRowNum(), curRoom, roomQueue);
	}

}

void battleScene::setRoomType()
{
	Vector<battleRoom*> vecRoom;                                //����ȷ�����ⷿ��(����߷�)
	//*****************************************************meaningless**//
	int cntDirEndRoom = 0;
	for (int dir = 0; dir < 4; dir++)
		if (_endRoom->_visDirection[dir] == true)
			cntDirEndRoom++;
	//*****************************************************
	for (int y = 0; y < NumRoomY; y++) 
	{                                                           //�жϷ������Ͳ����ɵ�ͼ
		for (int x = 0; x < NumRoomX; x++) 
		{
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			if (curRoom == nullptr) 
				continue;
			if (curRoom == _beginRoom)
				curRoom->_battleRoomType = TypeBegin;
			else if (curRoom == _endRoom) 
			{
				if (_battleSceneNumber % 5 == 0)                //�յ�Ϊboss����
					curRoom->_battleRoomType = TypeBoss;
				else
					curRoom->_battleRoomType = TypeEnd;
			}
			else
				curRoom->_battleRoomType = TypeNormal;

			bool notConnectedToBegin = true;
			//�ж�һ�������Ƿ���������� ��������Ϊ��ͨ���� ��������ѡ��
			for (int dir = 0; dir < 4; dir++) {
				if (curRoom == _beginRoom || curRoom == _endRoom) 
				{
					notConnectedToBegin = false;
					break;
				}
				if (curRoom->_visDirection[dir] == false) 
					continue;

				battleRoom* toRoom = _battleRoomMatrix[x + DirectionX[dir]][y + DirectionY[dir]];
				if (toRoom == _beginRoom)
					notConnectedToBegin = false;      //����ʼ������յ�����
			}
			if (notConnectedToBegin) 
				vecRoom.pushBack(curRoom);
		}
	}

	//log("room size %d", vecRoom.size());
	for (int i = 0, roomIndex = 0; i < 2; i++) 
	{  
		if (vecRoom.size() == 0) 
			break;
		roomIndex = rand() % vecRoom.size();          //���ѡһ������
		battleRoom* curRoom = vecRoom.at(roomIndex);
		vecRoom.erase(vecRoom.begin() + roomIndex);

		if (i == 0)
			curRoom->_battleRoomType = TypeBox;
		else if (i == 1)
			curRoom->_battleRoomType = TypeBox;
	}
}

void battleScene::initBattleRoomGenerate()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	countForRoom = 0;

	for (int y = 0; y < NumRoomY; y++)
	{ // 25 rooms
		for (int x = 0; x < NumRoomX; x++)
		{
			_battleRoomMatrix[x][y] = nullptr;
		}
	} // 25 roomss

	srand(static_cast<unsigned int>(time(nullptr)));

	beginRoomGenerate((NumRoomX) / 2, (NumRoomY) / 2);            //�ھ����������ɳ�ʼ����

	setRoomType();

	for (int y = 0; y < NumRoomY; y++) 
	{  // 25 rooms
		for (int x = 0; x < NumRoomX; x++) 
		{
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			if (curRoom == nullptr) continue;

			curRoom->Hero = Hero;
			curRoom->createBattleRoomMaping();
			memcpy(curRoom->_visDirectionCpy, curRoom->_visDirection, sizeof(curRoom->_visDirection));
		}
	}

}

void battleScene::setCorridorWithWidth(room* corridor,const battleRoom* fromBattleRoom,const battleRoom* toBattleRoom)
{
	corridor->_sizeX = SIZEOFCENTERDISTANCE - fromBattleRoom->_sizeX / 2 - toBattleRoom->_sizeX / 2 - 1;

	corridor->_topLeftCornerPositionX =fromBattleRoom->_centerX + WIDTHOFFLOOR * (fromBattleRoom->_sizeX / 2 + 1);
	corridor->_topLeftCornerPositionY = fromBattleRoom->_centerY + HEIGHTOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);

	corridor->_lowerRightCornerPositionX = toBattleRoom->_centerX - WIDTHOFFLOOR * (toBattleRoom->_sizeX / 2 + 1);
	corridor->_lowerRightCornerPositionY = toBattleRoom->_centerY - HEIGHTOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);
	corridor->createRoomMaping();
	////ȷ��С��ͼ���ƶ���
	//float downLeftX = miniMap->miniRoom[fromRoom->x][fromRoom->y]->upRightX;
	//float downLeftY = miniMap->miniRoom[fromRoom->x][fromRoom->y]->downLeftY + 7;
	//float upRightX = miniMap->miniRoom[toRoom->x][toRoom->y]->downLeftX;
	//float upRightY = miniMap->miniRoom[toRoom->x][toRoom->y]->upRightY - 7;
	//miniHall->drawSolidRect(Vec2(downLeftX, downLeftY), Vec2(upRightX, upRightY),
	//	Color4F(0.9f, 0.9f, 0.9f, 0.3f));
}

void battleScene::setCorridorWithHeight(room* corridor, const battleRoom* fromBattleRoom, const battleRoom* toBattleRoom)
{
	corridor->_sizeY = SIZEOFCENTERDISTANCE - fromBattleRoom->_sizeY / 2 - toBattleRoom->_sizeY / 2 - 1;

	corridor->_topLeftCornerPositionX = fromBattleRoom->_centerX - WIDTHOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);
	corridor->_topLeftCornerPositionY =fromBattleRoom->_centerY - HEIGHTOFFLOOR * (fromBattleRoom->_sizeY / 2 + 1);

	corridor->_lowerRightCornerPositionX = toBattleRoom->_centerX + WIDTHOFFLOOR * (SIZEOFCORRIDOR / 2 - 1);
	corridor->_lowerRightCornerPositionY = toBattleRoom->_centerY + HEIGHTOFFLOOR * (toBattleRoom->_sizeY / 2 + 1);
	corridor->createRoomMaping();
	////ȷ��С��ͼ���ƶ���
	//float downLeftX = miniMap->miniRoom[toRoom->x][toRoom->y]->downLeftX + 7;
	//float downLeftY = miniMap->miniRoom[toRoom->x][toRoom->y]->upRightY;
	//float upRightX = miniMap->miniRoom[fromRoom->x][fromRoom->y]->upRightX - 7;
	//float upRightY = miniMap->miniRoom[fromRoom->x][fromRoom->y]->downLeftY;
	//miniHall->drawSolidRect(Vec2(downLeftX, downLeftY), Vec2(upRightX, upRightY),
	//	Color4F(0.9f, 0.9f, 0.9f, 0.3f));
}

void battleScene::connectRoom(battleRoom* curRoom)
{
	assert(curRoom != nullptr);

	for (int dir = 0; dir < 4; dir++) { //4 directions
		if (curRoom->_visDirectionCpy[dir] == false) 
			continue;
		int toX = curRoom->_columnNum + DirectionX[dir];
		int toY = curRoom->_rowNum + DirectionY[dir];

		auto toRoom = _battleRoomMatrix[toX][toY];
		//auto curMiniRoom = miniMap->miniRoom[curRoom->x][curRoom->y];
		//auto toMiniRoom = miniMap->miniRoom[toX][toY];

		//auto miniHall = DrawNode::create(); //����С��ͼ����
		//miniHall->setGlobalZOrder(10);

//#ifndef DEBUG
//		miniHall->setVisible(false);
//#endif  // ! 

		auto corridor = room::create(); //���ɵ�ͼ����
		corridor->Hero = Hero;
		corridor->_direction = dir;

		switch (dir) {
		case RIGHT:
			setCorridorWithWidth(corridor, curRoom, toRoom);
			break;
		case UP:
			setCorridorWithHeight(corridor, toRoom, curRoom);
			break;
		case LEFT:
			setCorridorWithWidth(corridor, toRoom, curRoom);
			break;
		case DOWN:
			setCorridorWithHeight(corridor, curRoom, toRoom);
			break;
		}

		this->addChild(corridor);
		//miniMap->addChild(miniHall);
		vecCorridor.pushBack(corridor);

		curRoom->_visDirectionCpy[dir] = false;  //��ǲ�����������
		//curMiniRoom->miniHall[dir] = miniHall;
		toRoom->_visDirectionCpy[(dir + 2) % 4] = false;  //��ǲ�����������
		//toMiniRoom->miniHall[(dir + 2) % CNTDIR] = miniHall;

		connectRoom(toRoom);
		// need to fix vis
	}

}
