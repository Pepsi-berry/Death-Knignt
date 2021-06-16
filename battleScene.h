#ifndef _BATTTLE_SCENE_
#define _BATTLE_SCENE_

#include "cocos2d.h"
#include "battleRoom.h"
#include "hero.h"
#include "drop.h"

//class monster;

USING_NS_CC;

class battleScene : public Scene
{
	static constexpr int MaxRoom = 6;               //���ý�С�������Ա�֤����ʱ��
public:
	CREATE_FUNC(battleScene);

	virtual bool init();

	virtual void update(float delta);

	static int getBattleSceneNumber() { return _battleSceneNumber; }
	static int getBattleSceneType() { return _battleSceneType; }

	void setBattleSceneNumber(int battleSceneNumber) { _battleSceneNumber = battleSceneNumber; }
	void setBattleSceneType(int battleSceneType) { _battleSceneType = battleSceneType; }

	void setCorridorWithWidth(room* corridor, const battleRoom* fromBattleRoom, const battleRoom* toBattleRoom);     //�õ����ȵĶ���ͳ���
	void setCorridorWithHeight(room* corridor, const battleRoom* fromBattleRoom, const battleRoom* toBattleRoom);    //�õ����ȵĶ���ͳ���


	void initBattleRoomGenerate();                                          //��ʼ��ս�������ڵķ�������
	void beginRoomGenerate(int column, int row);                            //������ɵ���㼴��ʼ���������
	void nextRoomGenerate(int column, int row, battleRoom* curRoom, std::queue<battleRoom*>& roomQueue);     //������һ������
	void connectRoom(battleRoom* curRoom);                                  //�ӳ�ʼ���俪ʼ��������ͨ����
	void initEnemy();                                                       //��ʼ�����ɹ���
	void setRoomType();                                                     //���ùؿ������б���ʼ���ķ��������

	static Scene* createBattleScene();


	//void bindmonster(monster* mons);

	//monster* getmonster();


	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//�����ຯ��
	void updateBattleScenePosition();                                       //���������ƶ���ɵĻ���λ�ñ仯
	void updateRoomHeroLocated();                                           //����Ӣ����������(_curBattleRoom��_curCorridor)
	void updateBoundaryJudgement();                                         //����,���б߽��ж�
	void updateMonsterAttack(float delta);                                  //���¹��﹥��
	void updateBattleRoomDoorState();                                       //����battleRoom�ŵĿ���
	void updatePortalJudgement();                                           //���¶Դ������Լ��г������ж�

	//
	//

	/**/	
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	/**/





private:
	//monster* monsterforT;
	static int _battleSceneNumber;                                          //�����ؿ��ڵ�С�������
	static int _battleSceneType;                                            //��ؿ�����

	static hero* Hero;

	battleRoom* _beginRoom = nullptr;
	battleRoom* _endRoom = nullptr;
	battleRoom* _battleRoomMatrix[NumRoomX][NumRoomY] = { nullptr };        //��ʼ������λ��ѡȡ�ķ�Χ����

	//�������ɵ����е�ͼԪ�ص�ָ��,���ڶԵ�ͼԪ�صĹ���
	Vector<Sprite*> vecFloor;                                              
	Vector<Sprite*> vecWall;
	Vector<Sprite*> vecDoor;
	Vector<room*> vecCorridor;
	Vector<monster*>vecMonster;


	int countForRoom;

};



#endif // !_BATTTLE_SCENE_
