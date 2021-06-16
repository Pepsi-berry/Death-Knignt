#include "cocos2d.h"

USING_NS_CC;

#ifndef _DROP_H_
#define _DROP_H_

class drop : public Node {
public:
	drop() = default;
	~drop();
	CREATE_FUNC(drop);

	void bindSprite(Sprite* sprite);

	virtual bool init();

	int getmydamage()const;

	void settype();
	int gettype()const;

protected:
	int _dropType;
	Sprite* _dropsprite;
};

#endif
