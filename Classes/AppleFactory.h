#ifndef _APPLEFACTORY_H_
#define _APPLEFACTORY_H_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class AppleFactory
{
public:
	static Sprite* apple;
	static int x, y;
	static void createApple(Layer* layer);

};

#endif