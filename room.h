#ifndef _ROOM_
#define _ROOM_

#include "cocos2d.h"
#include "globalVariable.h"
#include "hero.h"

USING_NS_CC;
//�������ķ���(��������)
class room : public Node
{
	friend class battleScene;
public:
	CREATE_FUNC(room);

	virtual bool init();

	virtual void update(float delta);

	//���ݴ��������Ͳ���������Ӧ��ͼ
	void generateFloorMaping(float positionX, float positionY, int layer);
	void generateWallMaping(float positionX,float positionY,int layer);

	void setCenter(float centerX, float centerY) { _centerX = centerX, _centerY = centerY; }

	float getCenterX() { return _centerX; }
	float getCenterY() { return _centerY; }

	void createRoomMaping();                //���ú�������ӽڵ����ɽ��걸������ͼ

	void moveRoomPosition(float mvSpeedX,float mvSpeedY);   //�ƶ�����λ���Ը��»���

protected:
	float _centerX, _centerY;               //���������ĵ�����
	int _sizeX, _sizeY;                     //X,Y���������ͼ(����ǽ�ں͵ذ�)����(�������С)

	//��Ӷ�������,�Ա�����ӳ���Ҫ��ʱ����ֱ�۵�ѭ������
	float _topLeftCornerPositionX, _topLeftCornerPositionY, _lowerRightCornerPositionX, _lowerRightCornerPositionY;
	hero* Hero = NULL;                      //�ٿص���Ϸ����

	Vector <bullet*> vecBullet;             //����ӵ��ӵ���ַ�����Է�������״̬����


private:
	int _direction;                         //�������ȳ���
};



#endif // !_ROOM_
