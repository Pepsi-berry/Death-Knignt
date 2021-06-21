#ifndef _SECURE_ROOM_
#define _SECURE_ROOM_
#include "hero.h"
USING_NS_CC;


class secureRoom : public Scene {
public:
	void truekeycode(EventKeyboard::KeyCode keycode);

	void falsekeycode(EventKeyboard::KeyCode keycode);

	void updatekeyboard(float delta);

	static Scene* createScene();

	virtual bool init();


	virtual void update(float delta);

	CREATE_FUNC(secureRoom);


	/*�ص�����*/
	void menuCloseCallbackEnd(cocos2d::Ref* pSender);
	void menuCloseCallbackSet(cocos2d::Ref* pSender);
	void menuCloseCallbackVolumeUp(cocos2d::Ref* pSender);//��������
	void menuCloseCallbackVolumeDown(cocos2d::Ref* pSender);//��������
    hero* Hero;


private:
	/*�жϽ�ɫ�Ƿ���봫����*/
	bool isInDoor();
	int ischosen = 0;
private:
	Sprite* selectTip;
	Sprite* backGround;
	int BGM;
	cocos2d::Menu* MenuUpVolume;
	cocos2d::Menu* MenuDownVolume;
	/*������С��ǩ*/
	cocos2d::Label* volumeNumLab;


	/**/
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	/**/
};







#endif // !_SECURE_ROOM_
