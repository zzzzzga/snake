#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <iostream>
#include "cocos2d.h"
#include "Body.h"
#include "Util.h"
USING_NS_CC;

#define RIGHT_ANGLE 90
#define LEFT_ANGLE -90
#define UP_ANGLE 0
#define DOWN_ANGLE 180

typedef enum{
	LEFT,
	RIGHT,
	UP,
	DOWN
}Direction;


class Snake
{
public:
	std::vector<Body*> bodyArray;
	Node* node=NULL;
	int initLen = 3;
	Direction direction = Direction::LEFT;

public:
	Snake(Node * node );
	//蛇生长的函数
	void grow(bool);
	//获取蛇尾位置
	Point getTailGrid();

	void changeDirection(Direction dir);

	//
	Point OffSetGridByDir(int x, int y, Direction direction);

	//
	float getRotation();
	//
	void Update();

	bool collideApple();

	bool collideSelf();

	void kill();

	void Blink(std::function<void()> func);

	bool posInSnake(Point pos);

	bool collideWall();
};

#endif