#include "battleScene.h"
#include "set_scene.h"

hero* battleScene::Hero = nullptr;
int battleScene::_battleSceneNumber = 0;

void battleScene::bindmonster(monster* mons)
{
	monsterforT = mons;
}

monster* battleScene::getmonster()
{
	return monsterforT;
}

Scene* battleScene::createBattleScene()
{
	Scene* scene = Scene::createWithPhysics();
	//设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	battleScene* layer = battleScene::create();
	//把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}


bool battleScene::init()
{
	if (!Scene::init())
		return false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	initBattleRoomGenerate(); 
	connectRoom(_beginRoom); 

	//后期考虑将下述添加过程做函数拆分工作
	//添加英雄并对其完成初始化
	Hero = hero::create();
	Hero->initmem(5.0, 10, 10);
	Hero->bindscene(this);
	Hero->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	PhysicsBody* herobody = PhysicsBody::createBox(Hero->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	herobody->setGravityEnable(false);
	herobody->setDynamic(false);
	herobody->setCategoryBitmask(0x0001);
	herobody->setCollisionBitmask(0x0001);
	herobody->setContactTestBitmask(0x0001);
	Hero->addComponent(herobody);
	Hero->setTag(1);
	this->addChild(Hero, 0);


	monsterforT = monster::create();
	this->bindmonster(monsterforT);
	this->getmonster();
	this->getmonster()->setPosition(Point(visibleSize.width / 4, visibleSize.height / 4));
	PhysicsBody* physicsBody2 = PhysicsBody::createBox(this->getmonster()->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody2->setGravityEnable(false);
	physicsBody2->setDynamic(false);
	physicsBody2->setCategoryBitmask(0x0001);
	physicsBody2->setCollisionBitmask(0x0001);
	physicsBody2->setContactTestBitmask(0x0001);
	this->getmonster()->addComponent(physicsBody2);
	this->getmonster()->setTag(2);
	this->addChild(this->getmonster(), 0);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(battleScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();
	return true;
}

bool battleScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA && nodeB)
	{
		if (nodeB->getTag() == 2)
		{
			monsterforT = dynamic_cast<monster*>(nodeB);
			monsterforT->removeAllComponents();
			monsterforT->dead();
		}
		else 
		{
			monsterforT = dynamic_cast<monster*>(nodeA);
			monsterforT->removeAllComponents();
			monsterforT->dead();
		}
	}
    return true;
}

void battleScene::update(float delta)
{
	updateBattleScenePosition();
}

//暂时只包括视野移动
void battleScene::updateBattleScenePosition()
{
	float mvSpeedX = Hero->getmovespeedX();
	float mvSpeedY = Hero->getmovespeedY();

	CCLOG("mvSpeedX%f,mvSpeedY%f", mvSpeedX, mvSpeedY);

	for (int y = 0; y < NumRoomY; y++)
	{ //修改所有子节点战斗房间位置
		for (int x = 0; x < NumRoomY; x++)
		{
			if (_battleRoomMatrix[x][y] == nullptr)
				continue;
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			curRoom->moveRoomPosition(-mvSpeedX, -mvSpeedY);
		}
	}
	for (auto corridor : vecCorridor)
	{ //修改所有子节点走廊位置
		corridor->moveRoomPosition(-mvSpeedX, -mvSpeedY);
	}

}

void battleScene::nextRoomGenerate(int column, int row, battleRoom* curRoom, std::queue<battleRoom*>& roomQueue)
{
	//随关卡数增加增加房间的额外关卡机制，后续更新
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

		vecDirection.push_back(direction);            //联通的方向
	}

	if (vecDirection.empty()) 
		return;

	int countDirectionChosen = std::max(2U, (rand() % (vecDirection.size() + 1U)));

	//在可行方向中随机选取所需数目方向
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
	//从一个房间开始向四周扩展
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
	Vector<battleRoom*> vecRoom;                                //用于确定特殊房间(如道具房)
	//*****************************************************meaningless**//
	int cntDirEndRoom = 0;
	for (int dir = 0; dir < 4; dir++)
		if (_endRoom->_visDirection[dir] == true)
			cntDirEndRoom++;
	//*****************************************************
	for (int y = 0; y < NumRoomY; y++) 
	{                                                           //判断房间类型并生成地图
		for (int x = 0; x < NumRoomX; x++) 
		{
			battleRoom* curRoom = _battleRoomMatrix[x][y];
			if (curRoom == nullptr) 
				continue;
			if (curRoom == _beginRoom)
				curRoom->_battleRoomType = TypeBegin;
			else if (curRoom == _endRoom) 
			{
				if (_battleSceneNumber % 5 == 0)                //终点为boss房间
					curRoom->_battleRoomType = TypeBoss;
				else
					curRoom->_battleRoomType = TypeEnd;
			}
			else
				curRoom->_battleRoomType = TypeNormal;

			bool notConnectedToBegin = true;
			//判断一个房间是否与起点相连 相连则设为普通房间 否则待随机选择
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
					notConnectedToBegin = false;      //与起始房间和终点相连
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
		roomIndex = rand() % vecRoom.size();          //随机选一个房间
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

	beginRoomGenerate((NumRoomX) / 2, (NumRoomY) / 2);            //在矩阵中心生成初始房间

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
	////确定小地图绘制顶点
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
	////确定小地图绘制顶点
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

		//auto miniHall = DrawNode::create(); //生成小地图走廊
		//miniHall->setGlobalZOrder(10);

//#ifndef DEBUG
//		miniHall->setVisible(false);
//#endif  // ! 

		auto corridor = room::create(); //生成地图走廊
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

		curRoom->_visDirectionCpy[dir] = false;  //标记不能来回连接
		//curMiniRoom->miniHall[dir] = miniHall;
		toRoom->_visDirectionCpy[(dir + 2) % 4] = false;  //标记不能来回连接
		//toMiniRoom->miniHall[(dir + 2) % CNTDIR] = miniHall;

		connectRoom(toRoom);
		// need to fix vis
	}

}
