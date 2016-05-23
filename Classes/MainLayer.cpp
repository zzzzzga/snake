#include "MainLayer.h"
#include "Snake.h"
#include "AppleFactory.h"
#include "Util.h"
#include "ui/CocosGUI.h"

using namespace ui;

#define SCORE_LABEL 101

bool MainLayer::init()
{
	//初始化场景,蛇和苹果
	reset();

	//创建围墙
	createWall();

	//创建记分板
	createScore();
	
	auto origin = Director::getInstance()->getVisibleOrigin();

	rocker = HRocker::create("rock1.png", "rockbg1.png", origin+Point(100, 100));
	rocker->startRock();
	addChild(rocker, 2);

	Button* _exit = Button::create("exit.png", "exit.png");
	_exit->setPosition(Util::Grid2Pos(11, 0));
	addChild(_exit);
	

	Button* _pause = Button::create("pause.png", "pause.png");
	_pause->setPosition(Util::Grid2Pos(11, -3));
	addChild(_pause);
	

	Button* _continue = Button::create("continue_1.png", "continue_2.png", "continue_3.png");
	_continue->setPosition(Util::Grid2Pos(11, -6));
	_continue->setVisible(false);
	addChild(_continue);

	_exit->addClickEventListener([](Ref* pref){Director::getInstance()->end(); });
	_pause->addClickEventListener([=](Ref* pref){
		unschedule(CC_SCHEDULE_SELECTOR(MainLayer::CallBack));
		_continue->setVisible(true); });
	_continue->addClickEventListener([=](Ref* pref){schedule(CC_SCHEDULE_SELECTOR(MainLayer::CallBack), 0.3f);  _continue->setVisible(false); });

	//创建暂停按钮
	/*Button* pause = Button::create("startGame.png", "startGame.png");
	pause->addClickEventListener([](Ref* pSender){
	Director::getInstance()->pause();
	});
	pause->setPosition(Util::Grid2Pos(11, -2));
	pause->setContentSize(Size(99, 33));
	this->addChild(pause);*/

	//恢复按钮
	/*Button* resume = Button::create("startGame.png", "startGame.png");
	resume->addClickEventListener([](Ref* pSender){
		Director::getInstance()->resume();
	});
	resume->setPosition(Util::Grid2Pos(11, -4));
	pause->setContentSize(Size(99, 33));
	this->addChild(resume);*/

	//实现控制蛇的事件监听
	/*auto* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		Size winsize = Director::getInstance()->getVisibleSize();
		Point touchPoint = touch->getLocation();
		Point center = Vec2(winsize.width / 2, winsize.height / 2);
		auto target = static_cast<MainLayer*>(event->getCurrentTarget());

		Direction direction=MainLayer::pointPosition(touchPoint - center);
		if ((direction == RIGHT || direction == LEFT) && (snake->direction == RIGHT || snake->direction == LEFT))
		{
			return false;
		}
		if ((direction == UP || direction == DOWN) && (snake->direction == UP || snake->direction == DOWN))
		{
			return false;
		}
		snake->direction = direction;

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	*/

	//通过调度器实现蛇的移动
	schedule(CC_SCHEDULE_SELECTOR(MainLayer::CallBack), 0.3f);

	return true;
}

void MainLayer::createScore()
{
	Sprite * score = Sprite::create("score.png");
	score->setPosition(Util::Grid2Pos(11, 4));
	this->addChild(score);

	Label* label = Label::createWithTTF("x 0", "fonts/Marker Felt.ttf", 18);
	label->setPosition(Util::Grid2Pos(11, 2)+Point(0, 20));
	this->addChild(label, 0, SCORE_LABEL);
}

//创建围墙
void MainLayer::createWall()
{
	for (int i = -GRIDSUM; i <= GRIDSUM; i++)
	{
		Sprite* wall = Sprite::create("wall.png");
		wall->setPosition(Util::Grid2Pos(i, GRIDSUM));
		this->addChild(wall);
	}
	for (int i = -GRIDSUM; i <= GRIDSUM; i++)
	{
		Sprite* wall = Sprite::create("wall.png");
		wall->setPosition(Util::Grid2Pos(i, -GRIDSUM));
		this->addChild(wall);
	}
	for (int i = -GRIDSUM; i <= GRIDSUM; i++)
	{
		Sprite* wall = Sprite::create("wall.png");
		wall->setPosition(Util::Grid2Pos(GRIDSUM, i));
		this->addChild(wall);
	}
	for (int i = -GRIDSUM; i <= GRIDSUM; i++)
	{
		Sprite* wall = Sprite::create("wall.png");
		wall->setPosition(Util::Grid2Pos(-GRIDSUM, i));
		this->addChild(wall);
	}
}

void MainLayer::CallBack(float df)
{
	if (state==RUNNING)
	{
		Label* label = (Label*)this->getChildByTag(SCORE_LABEL);

		memset(scoreText, 0, sizeof(char)*10);
		sprintf(scoreText, "x %d", score);

		label->setString(scoreText);

		//摇杆控制
		if (rocker->getdir() != rock_default)
		{
			switch (rocker->getdir())
			{
			case rock_right:
				snake->changeDirection(RIGHT);
				break;
			case rock_left:
				snake->changeDirection(LEFT);
				break;
			case rock_down:
				snake->changeDirection(DOWN);
				break;
			case rock_up:
				snake->changeDirection(UP);
				break;
			default:
				break;
			}
		}

		snake->Update();
		//判断是否碰到苹果
		if (snake->collideApple())
		{
			score++;
			while (true)
			{
				AppleFactory::createApple(this);
				if (!snake->posInSnake(AppleFactory::apple->getPosition()))
				{
					break;
				}
			}
		}
		//判断是否碰到自身或者墙
		if (snake->collideSelf()||snake->collideWall())
		{
			CCLOG("collode  self");
			state = DEAD;
			snake->Blink([&](){
				reset();
			});
		}
	}
}
void MainLayer::reset()
{
	score = 0;
	if (snake!=NULL)
	{
		snake->kill();
		CC_SAFE_DELETE(snake);
	}
	//创建蛇,~MainLayer();释放内存
	snake = new Snake(this);

	//创建苹果
	while (true)
	{
		AppleFactory::createApple(this);
		if (!snake->posInSnake(AppleFactory::apple->getPosition()))
		{
			break;
		}	
	}
	state = RUNNING;

}

Direction MainLayer::pointPosition(Point p)
{
	if (std::abs(p.x)<std::abs(p.y)&&p.y>0)
	{
		return UP;
	}
	if (std::abs(p.x)<std::abs(p.y) && p.y<0)
	{
		return DOWN;
	}
	if (std::abs(p.x) > std::abs(p.y) && p.x < 0)
	{
		return LEFT;
	}
	if (std::abs(p.x) > std::abs(p.y) && p.x > 0)
	{
		return RIGHT;
	}
	return RIGHT;
}

MainLayer::~MainLayer()
{
	if (snake!=nullptr)
	{
		CC_SAFE_DELETE(snake);
	}
}
