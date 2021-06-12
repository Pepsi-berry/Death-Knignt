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
	//vecDoorOpen.pushBack(tmpSprite);

	tempSprite->setPosition(Point(positionX, positionY));
	tempSprite->setVisible(true);

	tempSprite = Sprite::create("Map//doorClose.png");
	this->addChild(tempSprite, layer);
	tempSprite->setGlobalZOrder(layer);
	//vecDoorClose.pushBack(tmpSprite);

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
			//Sprite* portal = Sprite::create("Map//portal3.png");
			//portal->setPosition(Point(_centerX, _centerY));
			//addChild(portal);
			//portal->setGlobalZOrder(-1);

			//this->portal = portal;
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
