#ifndef _MAINLAYER_H_
#define _MAINLAYER_H_

#include <iostream>
#include "cocos2d.h"
#include "Snake.h"
#include "HRocker.h"

typedef enum
{
	RUNNING,
	DEAD
}State;

USING_NS_CC;
class MainLayer:public Layer
{
public:
	CREATE_FUNC(MainLayer);
	virtual bool init();
	~MainLayer();

	void CallBack(float);
	static Direction pointPosition(Point p);
	void reset();
	void createWall();

	void createScore();

public:
	Snake* snake=NULL;
	State state = RUNNING;
	int score=0;
	char scoreText[10];
	HRocker* rocker;
};

#endif