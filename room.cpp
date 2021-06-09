#include "room.h"

bool room::init()
{
	_topLeftCornerPositionX = .0f;
	_topLeftCornerPositionY = .0f;
	_lowerRightCornerPositionX = .0f;
	_lowerRightCornerPositionY = .0f;
	_centerX = .0f;
	_centerY = .0f;
	_sizeX = SIZEOFROOM;
	_sizeY = SIZEOFROOM;

	this->scheduleUpdate();

	return true;
}

void room::update(float delta)
{

}

void generateFloorMaping(float positionX, float positionY, int layer)
{
	INT32 randomNum = rand();

	Sprite* tmpSprite = nullptr;


}

void generateWallMaping(float positionX, float positionY, int layer)
{

}

void room::createRoomMaping()
{

}