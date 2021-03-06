#ifndef _BATTTLE_SCENE_
#define _BATTLE_SCENE_

#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "battleRoom.h"
#include "secureRoom.h"
//#include "hero.h"
#include "drop.h"

//class monster;

USING_NS_CC;

class battleScene : public Scene
{
	friend class secureRoom;
	static constexpr int MaxRoom = 6;               //设置较小房间数以保证加载时间
public:
	CREATE_FUNC(battleScene);

	virtual bool init();

	virtual void update(float delta);

	void randomBGM();      //随机音乐bgm

	static int getBattleSceneNumber() { return _battleSceneNumber; }
	static int getBattleSceneType() { return _battleSceneType; }


	void setBattleSceneNumber(int battleSceneNumber) { _battleSceneNumber = battleSceneNumber; }
	void setBattleSceneType(int battleSceneType) { _battleSceneType = battleSceneType; }

	void setCorridorWithWidth(room* corridor, const battleRoom* fromBattleRoom, const battleRoom* toBattleRoom);     //得到走廊的顶点和长度
	void setCorridorWithHeight(room* corridor, const battleRoom* fromBattleRoom, const battleRoom* toBattleRoom);    //得到走廊的顶点和长度


	void initBattleRoomGenerate();                                          //初始化战斗场景内的房间生成
	void beginRoomGenerate(int column, int row);                            //完成生成的起点即初始房间的生成
	void nextRoomGenerate(int column, int row, battleRoom* curRoom, std::queue<battleRoom*>& roomQueue);     //生成下一个房间
	void connectRoom(battleRoom* curRoom);                                  //从初始房间开始用走廊联通房间
	void initEnemy();                                                       //初始化生成怪物
	void setRoomType();                                                     //设置关卡矩阵中被初始化的房间的类型

	static Scene* createBattleScene();


	//void bindmonster(monster* mons);

	//monster* getmonster();


	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//更新类函数
	void updateBattleScenePosition();                                       //更新人物移动造成的画面位置变化
	void updateRoomHeroLocated();                                           //更新英雄所处房间(_curBattleRoom或_curCorridor)
	void updateBoundaryJudgement();                                         //更新,进行边界判定
	void updateMonsterAttack(float delta);                                  //更新怪物攻击
	void updateBattleRoomDoorState();                                       //更新battleRoom门的开关
	void updatePortalJudgement();                                           //更新对传送门以及切场景的判定
	void updateGameLose();                                                  //更新对游戏失败的判定
	void updateUILoading();                                                 //更新状态条信息
	void updateHeroArmor(float delta);                                      //更新护甲在不受攻击一段时间后随时间回复
	void updateSkillCooling(float delta);                                   //更新技能冷却
	void updateBossState();                                                 //更新boss状态,当前用于判定是否加入传送门和箱子

	//
	//

	/**/	
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	/**/

	 //回调
	void menuCloseCallbackEnd(Ref* pSender);
	void menuCloseCallbackSet(Ref* pSender);
	void menuCloseCallbackVolumeUp(cocos2d::Ref* pSender);//升高音量
	void menuCloseCallbackVolumeDown(cocos2d::Ref* pSender);//降低音量



private:
	//monster* monsterforT;
	static int _battleSceneNumber;                                          //代表大关卡内的小场景编号
	static int _battleSceneType;                                            //大关卡类型

	static hero* Hero;

	battleRoom* _beginRoom = nullptr;
	battleRoom* _endRoom = nullptr;
	battleRoom* _battleRoomMatrix[NumRoomX][NumRoomY] = { nullptr };        //初始化房间位置选取的范围矩阵

	//储存生成的下列地图元素的指针,用于对地图元素的管理
	Vector<Sprite*> vecFloor;                                              
	Vector<Sprite*> vecWall;
	Vector<Sprite*> vecDoor;
	Vector<room*> vecCorridor;
	Vector<monster*>vecMonster;

	//储存英雄的状态信息,完成不同场景之间的传递
	static int _heroStateType;
	static int _heroStateHP;
	static int _heroStateMP;
	static int _heroStateArmor;
	static int _heroStateCoin;
	static int _heroStateCurWeaponType;
	static int _heroStateSecondaryWeaponType;


	int countForRoom;
	int _recoveryCoolingTime = 0;
	int _skillCoolingTime = 0;

	//状态条
	ui::LoadingBar* HPLoadingBar = ui::LoadingBar::create();
	ui::LoadingBar* ARMORLoadingBar = ui::LoadingBar::create();
	ui::LoadingBar* MPLoadingBar = ui::LoadingBar::create();
	//状态条的数字
	Label* HPnum;
	Label* ARMORnum;
	Label* MPnum;
	Label* COINnum;
	Sprite* CoinPng;
	int BGM;
	cocos2d::Menu* MenuUpVolume;
	cocos2d::Menu* MenuDownVolume;
	/*音量大小标签*/
	cocos2d::Label* volumeNumLab;
};



#endif // !_BATTTLE_SCENE_
