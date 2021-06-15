#include "room.h"
#include "battleScene.h"

bool room::init()
{
	_topLeftCornerPositionX = .0f;
	_topLeftCornerPositionY = .0f;
	_lowerRightCornerPositionX = .0f;
	_lowerRightCornerPositionY = .0f;
	_centerX = .0f;
	_centerY = .0f;
	_sizeX = SIZEOFCORRIDOR;
	_sizeY = SIZEOFCORRIDOR;

	this->scheduleUpdate();

	return true;
}

bool room::getIsAtRoom(hero* Hero)
{
	float curHeroPositionX = Hero->getPositionX();
	float curHeroPositionY = Hero->getPositionY();
	if (curHeroPositionX > _topLeftCornerPositionX - WIDTHOFFLOOR && curHeroPositionX < _lowerRightCornerPositionX + WIDTHOFFLOOR &&
		curHeroPositionY < _topLeftCornerPositionY + HEIGHTOFFLOOR && curHeroPositionY > _lowerRightCornerPositionY - HEIGHTOFFLOOR)
		return true;
	return false;
}

void room::moveRoomPosition(float mvSpeedX,float mvSpeedY)
{
	_topLeftCornerPositionX += mvSpeedX;
	_topLeftCornerPositionY += mvSpeedY;
	_lowerRightCornerPositionX += mvSpeedX;
	_lowerRightCornerPositionY += mvSpeedY;
	_centerX += mvSpeedX;
	_centerY += mvSpeedY;

	for (auto child : getChildren())
	{
		float curPositionX = child->getPositionX(), curPositionY = child->getPositionY();
		child->setPosition(Point(curPositionX + mvSpeedX, curPositionY + mvSpeedY));
	}
}

void room::update(float delta)
{

}

void room::generateFloorMaping(float positionX, float positionY, int layer)
{
	int randomNum = rand();               //针对随机数获取方式后续可进行改进

	Sprite* tempSprite = nullptr;

	//int sceneTypeIndex = battleScene::getBattleSceneNumber();
	//sceneTypeIndex = sceneTypeIndex % 5 == 0 ? sceneTypeIndex / 5 : sceneTypeIndex / 5 + 1;
	//(sceneTypeIndex -= 1) %= battleScene::getVecSceneType().size();
	//Value imageName = Value(battleScene::getVecSceneType().at(sceneTypeIndex));
	//选取场景类型

	std::string textureName;
	if (randomNum % 4 == 0)
		textureName = "Map//floor3.png";
	else if (randomNum % 3 == 0)
		textureName = "Map//floor2.png";
	else
		textureName = "Map//floor1.png";

	tempSprite = Sprite::create(textureName);
	tempSprite->setGlobalZOrder(layer);
	tempSprite->setPosition(Point(positionX, positionY));
	this->addChild(tempSprite);
	//vecFloor.pushBack(tempSprite);


}

void room::generateWallMaping(float positionX, float positionY, int layer)
{
	int randomNum = rand();               //针对随机数获取方式后续可进行改进

	Sprite* tempSprite = nullptr;

	//int sceneTypeIndex = battleScene::getBattleSceneNumber();
	//sceneTypeIndex = sceneTypeIndex % 5 == 0 ? sceneTypeIndex / 5 : sceneTypeIndex / 5 + 1;
	//(sceneTypeIndex -= 1) %= battleScene::getVecSceneType().size();
	//Value imageName = Value(battleScene::getVecSceneType().at(sceneTypeIndex));
	//选取场景类型

	std::string textureName;
	if (randomNum % 6 == 0)
		textureName = "Map//wall2.png";
	else
		textureName = "Map//wall1.png";

	tempSprite = Sprite::create(textureName);
	tempSprite->setGlobalZOrder(layer);
	tempSprite->setPosition(Point(positionX, positionY + (HEIGHTOFWALL - HEIGHTOFFLOOR)));
	this->addChild(tempSprite);
	//vecFloor.pushBack(tempSprite);
}

void room::createRoomMaping()
{
	srand(time(nullptr));

	//CCLOG("%d,%d", _topLeftCornerPositionX, _topLeftCornerPositionY);


	const float X = _topLeftCornerPositionX - (_direction % 2 == 0 ? 0 : WIDTHOFFLOOR);
	const float Y = _topLeftCornerPositionY + (_direction % 2 == 0 ? HEIGHTOFFLOOR : 0);
	//(X, Y) is upLeft Position;

	float curX = X, curY = Y;
	for (int H = _sizeY - 1; H >= 0; H--) 
	{  // for height and width
		for (int W = 0; W <= _sizeX - 1; W++) 
		{
			if ((_direction % 2 == 0) && (H == 0 || H == _sizeY - 1)) 
			{
				if (H == 0)
					generateWallMaping(curX, curY, 1);
				else
					generateWallMaping(curX, curY, -1);
			}
			else if ((_direction % 2 == 1) && (W == 0 || W == _sizeX - 1)) 
				generateWallMaping(curX, curY, 1);
			else 
				generateFloorMaping(curX, curY, -2);
			// randomly generate floor and Wall
			curX += WIDTHOFFLOOR;
		}
		curX = X, curY -= HEIGHTOFFLOOR;
	}
}