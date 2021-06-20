#include "cocos2d.h"
#include "hero.h"

USING_NS_CC;

#ifndef _DROP_H_
#define _DROP_H_

class drop : public Node {
public:
	drop() = default;
	~drop();
	CREATE_FUNC(drop);

	void changetype(int changeType);

	void bindSprite(Sprite* sprite);

	virtual bool init();

	void propsUsing(hero* Hero);

	void settype();
	int gettype()const;
	int getDropPrice() { return _dropPrice; }
	void setIsUsed(bool isUsed) { _isUsed = isUsed; }
	bool getIsUsed() { return _isUsed; }

protected:
	int _dropType;
	int _dropPrice;
	bool _isUsed;
	Sprite* _dropsprite;
};

#endif
