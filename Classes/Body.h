#ifndef _BODY_H_
#define _BODY_H_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class Body
{
	CC_SYNTHESIZE(int, X, X);
	CC_SYNTHESIZE(int, Y, Y);

public:
	Body(int x, int y, Node* layer, bool isHead);
	void update();

public:

	Sprite* sp;
};

#endif