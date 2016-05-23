#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

//����Ĵ�С
#define GRIDSIZE 33

//���������
#define GRIDSUM 7


class Util
{
public:
	//����������ת��Ϊʵ�ʵ���������
	static Point Grid2Pos(int x, int y)
	{
		Size winsize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();
		return origin + Vec2(winsize.width / 2 + x*GRIDSIZE, winsize.height / 2 + y*GRIDSIZE);
	}
};

#endif