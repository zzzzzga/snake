#include "HRocker.h"

HRocker* HRocker::create(char* rockImg, char* rockBgImg, Point pos)
{
	HRocker* rocker = new HRocker();

	if (rocker&&rocker->init(rockImg, rockBgImg, pos))
	{
		rocker->autorelease();
		return rocker;
	}

	CC_SAFE_DELETE(rocker);

	return NULL;
}

bool HRocker::init(char* rockImg, char* rockBgImg, Point pos)
{
	rockPosition = pos;
	isCanMove = false;

	//摇杆中心的圆
	auto rock = Sprite::create(rockImg);
	rock->setPosition(pos);
	rock->setVisible(false);
	this->addChild(rock, 1, tag_rock);

	//摇杆外圈的圆
	auto rockbg = Sprite::create(rockBgImg);
	rockbg->setPosition(pos);
	rockbg->setVisible(false);
	this->addChild(rockbg, 0, tag_rockBg);
	rockBGR = rockbg->getContentSize().width / 2;	//外圈的半径
	rockR = rock->getContentSize().width / 2;

	return true;
}

void HRocker::startRock()
{
	auto rock = getChildByTag(tag_rock);
	auto rockbg = getChildByTag(tag_rockBg);

	rock->setVisible(true);
	rockbg->setVisible(true);


	//添加触摸事件
	auto* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HRocker::stopRocker()
{
	auto rock = getChildByTag(tag_rock);
	auto rockbg = getChildByTag(tag_rockBg);

	rock->setVisible(false);
	rockbg->setVisible(false);

	_eventDispatcher->removeEventListenersForTarget(this);
}

bool HRocker::onTouchBegan(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	auto rock = getChildByTag(tag_rock);

	if (rock->getBoundingBox().containsPoint(pos))
	{
		isCanMove = true;
		return true;
	}

	return false;
}

void HRocker::onTouchMoved(Touch* touch, Event* event)
{
	auto rock = getChildByTag(tag_rock);
	auto rockbg = getChildByTag(tag_rockBg);
	if (!isCanMove)
	{
		return;
	}
	Point pos = touch->getLocation();

	float angle = getRad(pos, rockPosition);


	if (isInner(pos))
	{
		//pos在外圈内则, 内圈直接将位置设置为pos
		rock->setPosition(pos);
	}
	else
	{
		//pos在圈外
		rock->setPosition(Vec2(sin(angle)*(rockBGR-rockR), cos(angle)*(rockBGR-rockR))+rockPosition);
	}

	if (angle<PI/4&&angle>-PI/4)
	{
		dir = rock_up;
	}
	else if (angle>PI/4 && angle<PI*3/4)
	{
		dir = rock_right;
	}
	else if (angle>PI*3/4 || angle<-PI*3/4)
	{
		dir = rock_down;
	}
	else if (angle>PI* -3/4&&angle<-PI/4)
	{
		dir = rock_left;
	}

	//CCLOG("%f, %f, %d", angle, angle/PI*180, dir);

}

void HRocker::onTouchEnded(Touch* touch, Event* event)
{
	if (!isCanMove)
	{
		return;
	}
	auto rock = getChildByTag(tag_rock);

	MoveTo* move = MoveTo::create(0.3f, rockPosition);
	rock->stopAllActions();
	rock->runAction(move);
	isCanMove = false;

	dir = rock_default;
}

//返回两点之间与y轴的正半轴的角度
float HRocker::getRad(Point p1, Point p2)
{
	float detax = p1.x - p2.x;
	float detay = p1.y - p2.y;
	float xie = sqrt(pow(detax, 2)+pow(detay, 2));

	float angle = acos(detay / xie);

	if (p1.x<p2.x)
	{
		angle = -angle;
	}

	return angle;
}

bool HRocker::isInner(Point pos)
{
	float detax = pos.x - rockPosition.x;
	float detay = pos.y - rockPosition.y;

	if (rockBGR-rockR>sqrt(pow(detax,2) + pow(detay,2)))
	{
		return true;
	}
	else
	{
		return false;
	}
}