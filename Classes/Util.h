#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

//网格的大小
#define GRIDSIZE 33

//网格的数量
#define GRIDSUM 7


class Util
{
public:
	//将网格坐标转化为实际的像素坐标
	static Point Grid2Pos(int x, int y)
	{
		Size winsize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();
		return origin + Vec2(winsize.width / 2 + x*GRIDSIZE, winsize.height / 2 + y*GRIDSIZE);
	}
};

#endif