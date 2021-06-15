#include "battleRoom.h"
#include "battleScene.h"




bool battleRoom::init()
{
	_topLeftCornerPositionX = .0f;
	_topLeftCornerPositionY = .0f;
	_lowerRightCornerPositionX = .0f;
	_lowerRightCornerPositionY = .0f;
	_centerX = .0f;
	_centerY = .0f;
	_sizeX = SIZEOFROOM;
	_sizeY = SIZEOFROOM;
	_battleRoomType = TypeNormal;

	this->scheduleUpdate();
	return true;
}

void battleRoom::update(float delta)
{

}

void battleRoom::generateDoorMaping(float positionX, float positionY, int layer)
{
	Sprite* tempSprite = Sprite::create("Map//doorOpen.png");
	this->addChild(tempSprite,  - 2);
	tempSprite->setGlobalZOrder( - 2);
	vecDoorOpened.pushBack(tempSprite);

	tempSprite->setPosition(Point(positionX, positionY));
	tempSprite->setVisible(true);

	tempSprite = Sprite::create("Map//doorClose.png");
	this->addChild(tempSprite, layer);
	tempSprite->setGlobalZOrder(layer);
	vecDoorClosed.pushBack(tempSprite);

	tempSprite->setPosition(Point(positionX, positionY + HEIGHTOFFLOOR / 2));
	tempSprite->setVisible(false);  // closeDoor images are not visible at first

}

void battleRoom::createBox(float positionX,float positionY)
{
	Sprite* box = Sprite::create("Box//box1.png");
	box->setPosition(Vec2(positionX, positionY));
	box->setGlobalZOrder(-2);
	this->addChild(box, 10);
	this->getVecBox().pushBack(box);
}

void battleRoom::createMonster()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int monsterNumber = 2 + rand() % 4;                           //随机初始化敌人产生数目
	for (int i = 1; i <= monsterNumber; i++)
	{
		float enemyPositionX = _centerX + (rand()) % 300;
		float enemyPositionY = _centerY + (rand()) % 300;
		monster* tempMonster = monster::create();
		tempMonster->bindAtBattleRoom(this);
		tempMonster->setPosition(Point(enemyPositionX, enemyPositionY));
		PhysicsBody* physicsBody2 = PhysicsBody::createBox(tempMonster->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody2->setGravityEnable(false);
		physicsBody2->setDynamic(false);
		physicsBody2->setCategoryBitmask(0x0001);
		physicsBody2->setCollisionBitmask(0x0001);
		physicsBody2->setContactTestBitmask(0x0001);
		tempMonster->addComponent(physicsBody2);
		tempMonster->setTag(2);
		_vecMonster.pushBack(tempMonster);
		this->addChild(tempMonster, 0);

		//tempMonster->bindAtBattleRoom(this);                    //绑定所在房间
		//tempMonster->startCount = i * 2;
		// 
		//auto monsterforT = monster::create();
		////this->bindmonster(monsterforT);
		////this->getmonster();
		//monsterforT->setPosition(Point((visibleSize.width * (i + 1)) / 5, (visibleSize.height * (i + 1)) / 5));
		//PhysicsBody* physicsBody2 = PhysicsBody::createBox(monsterforT->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		//physicsBody2->setGravityEnable(false);
		//physicsBody2->setDynamic(false);
		//physicsBody2->setCategoryBitmask(0x0001);
		//physicsBody2->setCollisionBitmask(0x0001);
		//physicsBody2->setContactTestBitmask(0x0001);
		//monsterforT->addComponent(physicsBody2);
		//monsterforT->setTag(2);
		//vecMonster.pushBack(monsterforT);
		//this->addChild(monsterforT, 0);
	}

}

void battleRoom::createBattleRoomMaping()
{
	srand(time(nullptr));

	//if (_battleRoomType == TypeEnd || _battleRoomType ==TypeWeapon  || roomType == TypeProp)
	if (_battleRoomType == TypeEnd || _battleRoomType ==TypeBox)
	{
		_sizeX -= 6, _sizeY -= 6;

		if (_battleRoomType == TypeEnd)
		{  //设置房间大小以及传送门
			_sizeX -= 2, _sizeY -= 2;
			Sprite* portal = Sprite::create("Map//portal3.png");
			portal->setPosition(Point(_centerX, _centerY));
			addChild(portal);
			portal->setGlobalZOrder(-1);

			this->_portal = portal;
		}
	}
	else if (_battleRoomType == TypeBoss)
	{
		_sizeX += 6, _sizeY += 6;
	}

	//addMapElement   添加地图元素 : 地板 墙 门
	const float X = _centerX - WIDTHOFFLOOR * (_sizeX / 2);
	const float Y = _centerY + HEIGHTOFFLOOR * (_sizeY / 2);
	//(X, Y) is upLeft Position;
	_topLeftCornerPositionX = X + WIDTHOFFLOOR;
	_topLeftCornerPositionY = Y - HEIGHTOFFLOOR;
	// get vertices Position
	_lowerRightCornerPositionX = X + WIDTHOFFLOOR * (_sizeX - 2);
	_lowerRightCornerPositionY = Y - HEIGHTOFFLOOR * (_sizeY - 2);

	CCLOG("%f,%f", _centerX, _centerY);
	//CCLOG("%d,%d", X, Y);
	//CCLOG("%d,%d", _topLeftCornerPositionX, _lowerRightCornerPositionX);
	float curX = X, curY = Y;
	for (int y = _sizeY - 1; y >= 0; y--) 
	{  // for height and width
		for (int x = 0; x <= _sizeX - 1; x++) 
		{
			if (y == 0 || y == _sizeY - 1 || x == 0 || x == _sizeX - 1) 
			{
				if (((x == 0) && _visDirection[LEFT] && ((_sizeY / 2) - 2 <= y) &&
					(y <= _sizeY / 2 - 2 + SIZEOFCORRIDOR - 3)) ||

					((x == _sizeX - 1) && _visDirection[RIGHT] &&
						(_sizeY / 2 - 2 <= y) &&
						(y <= _sizeY / 2 - 2 + SIZEOFCORRIDOR - 3)) ||

					((y == 0) && _visDirection[DOWN] && ((_sizeX / 2) - 2 <= x) &&
						(x <= _sizeX / 2 - 2 + SIZEOFCORRIDOR - 3)) ||

					((y == _sizeY - 1) && _visDirection[UP] && ((_sizeX / 2) - 2 <= x) &&
						(x <= _sizeX / 2 - 2 + SIZEOFCORRIDOR - 3))) 
				{
					if (y != _sizeY - 1)
						generateDoorMaping(curX, curY, 1);
					else
						generateDoorMaping(curX, curY, -1);
				}
				else if (y != _sizeY - 1 || x == 0 || x == _sizeX - 1) 
				{
					if (y == _sizeY / 2 + SIZEOFCORRIDOR - 4)
						generateWallMaping(curX, curY, 1);
					else
						generateWallMaping(curX, curY, 1);
				}
				else if (_visDirection[UP] && y == _sizeY - 1 &&
					(x == _sizeX / 2 - 3 ||
						x == _sizeX / 2 + SIZEOFCORRIDOR - 4))
				{
					generateWallMaping(curX, curY, 2);
				}
				else 
				{
					if (y == _sizeY - 1)  //上方的墙添加阴影
						generateWallMaping(curX, curY, -1);
					else
						generateWallMaping(curX, curY, -1);
				}
			}
			else 
			{
				generateFloorMaping(curX, curY, -2);
			}  // randomly generate floor and Wall

			curX += WIDTHOFFLOOR;
		}
		curX = X, curY -= HEIGHTOFFLOOR;
	}

	//if (roomType == PROP)
	//	generateStatue();
	if (_battleRoomType == TypeBox)
		createBox((_topLeftCornerPositionX + _lowerRightCornerPositionX) / 2, (_topLeftCornerPositionY + _lowerRightCornerPositionY) / 2);

	if (_battleRoomType == TypeEnd)
		;

}

bool battleRoom::createBattleRoom(battleRoom*& toBattleRoom, battleRoom* curBattleRoom, int direction, int toX, int toY)
{
	if (toBattleRoom != nullptr)
	{
		curBattleRoom->_visDirection[direction] = true;
		toBattleRoom->_visDirection[(direction + 2) % 4] = true;

		return false;
	}

	toBattleRoom = battleRoom::create();

	toBattleRoom->_columnNum = toX, toBattleRoom->_rowNum = toY;
	//log("%d %d", toX, toY);
	toBattleRoom->setCenter(curBattleRoom->_centerX + DirectionX[direction] * CENTERDISTANCE,
		curBattleRoom->_centerY + DirectionY[direction] * CENTERDISTANCE);

	curBattleRoom->_visDirection[direction] = true;
	toBattleRoom->_visDirection[(direction + 2) % 4] = true;
	return true;
}

void battleRoom::setDoorOpened() 
{ 
	for (auto spriteDoor : vecDoorOpened)
		spriteDoor->setVisible(true);
	for (auto spriteDoor : vecDoorClosed) 
		spriteDoor->setVisible(false);
}

void battleRoom::setDoorClosed()
{
	for (auto spriteDoor : vecDoorClosed)
		spriteDoor->setVisible(true);

	for (auto spriteDoor : vecDoorOpened)
		spriteDoor->setVisible(false);
}

bool battleRoom::getIsClearance()
{
	bool isClearance = true;
	for (auto curMonster : this->getVecMonster())
	{
		if (!curMonster->isdead())
		{
			isClearance = false;
			break;
		}
	}
	return isClearance;
}

void battleRoom::checkBattleRoomBoundaryBarrier(hero* Hero)
{
	float heroPositionX = Hero->getPositionX();
	float heroPositionY = Hero->getPositionY();
	if (this->getIsClearance())
	{
		if (((_topLeftCornerPositionY + HEIGHTOFFLOOR / 2 - HEIGHTOFFLOOR * (_sizeY / 2 - 3)) >=
			heroPositionY &&
			heroPositionY >= (_lowerRightCornerPositionY + HEIGHTOFFLOOR * (_sizeY / 2 - 3))))
		{
			if (Hero->getmovespeedX() > 0 && heroPositionX >= _lowerRightCornerPositionX && !_visDirection[RIGHT])
				//ispeedX = .0f;
				Hero->setmovespeedX(.0f);
			if (Hero->getmovespeedX() < 0 && heroPositionX <= _topLeftCornerPositionX && !_visDirection[LEFT])
				Hero->setmovespeedX(.0f);
		}
		else if (_topLeftCornerPositionX + HEIGHTOFFLOOR * (_sizeY / 2 - 3) <= heroPositionX &&                     //??
			heroPositionX <= _lowerRightCornerPositionX - HEIGHTOFFLOOR * (_sizeY / 2 - 3))
		{
			if (Hero->getmovespeedY() > 0 && heroPositionY >= _topLeftCornerPositionY + HEIGHTOFFLOOR / 2 && !_visDirection[UP])
				Hero->setmovespeedY(.0f);
			if (Hero->getmovespeedY() < 0 && heroPositionY <= _lowerRightCornerPositionY && !_visDirection[DOWN])
				Hero->setmovespeedY(.0f);
		}
		else
		{
			if (Hero->getmovespeedX() > 0 && heroPositionX >= _lowerRightCornerPositionX)
				Hero->setmovespeedX(.0f);
			if (Hero->getmovespeedX() < 0 && heroPositionX <= _topLeftCornerPositionX)
				Hero->setmovespeedX(.0f);
			if (Hero->getmovespeedY() > 0 && heroPositionY >= _topLeftCornerPositionY + 20)
				Hero->setmovespeedY(.0f);
			if (Hero->getmovespeedY() < 0 && heroPositionY <= _lowerRightCornerPositionY)
				Hero->setmovespeedY(.0f);
		}
	}
	else
	{
		if (Hero->getmovespeedX() > 0 && heroPositionX >= _lowerRightCornerPositionX)
			Hero->setmovespeedX(.0f);
		if (Hero->getmovespeedX() < 0 && heroPositionX <= _topLeftCornerPositionX)
			Hero->setmovespeedX(.0f);
		if (Hero->getmovespeedY() > 0 && heroPositionY >= _topLeftCornerPositionY + 20)
			Hero->setmovespeedY(.0f);
		if (Hero->getmovespeedY() < 0 && heroPositionY <= _lowerRightCornerPositionY)
			Hero->setmovespeedY(.0f);

	}
}

//
//bool battleRoom::getIsAtBattleRoom(hero* Hero)
//{
//	float heroPositionX = Hero->getPositionX();
//	float heroPositionY = Hero->getPositionY();
//
//	//CCLOG("%d,%d",_columnNum, _rowNum);
//	//CCLOG("heroPositionX %f,heroPositionY %f,_topLeftCornerPositionX %f,_topLeftCornerPositionY %f, _lowerRightCornerPositionX %f,_lowerRightCornerPositionY %f", heroPositionX, heroPositionY, _topLeftCornerPositionX, _topLeftCornerPositionY
//		//, _lowerRightCornerPositionX, _lowerRightCornerPositionY);
//	if (heroPositionX >= _topLeftCornerPositionX - WIDTHOFFLOOR && heroPositionX <= _lowerRightCornerPositionX + WIDTHOFFLOOR
//		&& heroPositionY >= _lowerRightCornerPositionY - HEIGHTOFFLOOR && heroPositionY <= _topLeftCornerPositionY + HEIGHTOFFLOOR)
//		return true;
//	else
//		return false;
//}
