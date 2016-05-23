#ifndef _HROCKER_H_
#define _HROCKER_H_

#include <iostream>
#include "cocos2d.h"

#define PI 3.1415927

typedef enum{
	rock_default =0,
	rock_right,
	rock_left,
	rock_up,
	rock_down
}rockDir;

typedef enum
{
	tag_rock=0,
	tag_rockBg
}tagType;

USING_NS_CC;
class HRocker:public Layer
{
public:
	static HRocker* create(char* rockImg, char* rockBgImg, Point pos);

	bool init(char* rockImg, char* rockBgImg, Point pos);

	void startRock();
	void stopRocker();

	rockDir getdir(){ return dir; }

private:

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	bool isInner(Point pos);
	float getRad(Point p1, Point p2);


	Vec2 rockPosition;	//摇杆中心的位置

	bool isCanMove;		//摇杆是否能动

	float rockBGR;		//摇杆背景的半径

	float rockR;     //内圈半径

	rockDir dir = rock_default; //摇杆的方向
};

#endif