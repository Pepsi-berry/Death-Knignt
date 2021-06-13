#ifndef _ROOM_
#define _ROOM_

#include "cocos2d.h"
#include "globalVariable.h"
#include "hero.h"

USING_NS_CC;
//代表抽象的房间(包含走廊)
class room : public Node
{
	friend class battleScene;
public:
	CREATE_FUNC(room);

	virtual bool init();

	virtual void update(float delta);

	//根据传入的坐标和层数载入相应贴图
	void generateFloorMaping(float positionX, float positionY, int layer);
	void generateWallMaping(float positionX,float positionY,int layer);

	void setCenter(float centerX, float centerY) { _centerX = centerX, _centerY = centerY; }

	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }

	void createRoomMaping();                //调用函数添加子节点生成较完备房间贴图

	void moveRoomPosition(float mvSpeedX,float mvSpeedY);   //移动房间位置以更新画面

protected:
	float _centerX, _centerY;               //代表房间中心点坐标
	int _sizeX, _sizeY;                     //X,Y方向填充贴图(包含墙壁和地板)数量(代表房间大小)

	//添加顶角坐标,以便于添加场景要素时进行直观的循环遍历
	float _topLeftCornerPositionX, _topLeftCornerPositionY, _lowerRightCornerPositionX, _lowerRightCornerPositionY;
	hero* Hero = NULL;                      //操控的游戏主角

	Vector <bullet*> vecBullet;             //将添加的子弹地址储存以方便管理和状态更新


private:
	int _direction;                         //代表走廊朝向
};



#endif // !_ROOM_
