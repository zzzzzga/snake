#include "LoadLayer.h"
#include "ui/CocosGUI.h"

using namespace ui;

bool LoadLayer::init()
{
	Size winSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	Sprite * bg_img = Sprite::create("bg.png");
	bg_img->setPosition(origin+Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(bg_img, 0);

	Button * start_button = Button::create("startGame.png", "startGame.png");
	start_button->addClickEventListener(CC_CALLBACK_1(LoadLayer::startGame, this));
	start_button->setPosition(origin+Vec2(winSize.width / 2, winSize.height / 4));
	this->addChild(start_button, 1, 100);

	auto option = createButton("option.png", "option.png", winSize.width / 2 - 200, winSize.height / 8, CC_CALLBACK_1(LoadLayer::optionCallBack, this));
	auto question = createButton("question.png", "question.png", winSize.width / 2, winSize.height / 8, CC_CALLBACK_1(LoadLayer::questionCallBack, this));
	auto exit = createButton("exit.png", "exit.png", winSize.width / 2 + 200, winSize.height / 8, CC_CALLBACK_1(LoadLayer::exitCallBack, this));

	this->addChild(option,1);
	this->addChild(question, 1);
	this->addChild(exit, 1);

	return true;
}

void LoadLayer::startGame(Ref* pSender)
{
	CCLOG("start Game!");
	tsm->goMainScene();
}

void LoadLayer::optionCallBack(Ref* pSender)
{
	CCLOG("option");
}

void LoadLayer::questionCallBack(Ref * pSender)
{
	CCLOG("question");
}
void LoadLayer::exitCallBack(Ref * pSender)
{
	CCLOG("exit");
	Director::getInstance()->end();
}

Button* LoadLayer::createButton(const char * normal, const char * selected, float x, float y, const Widget::ccWidgetClickCallback& callback)
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	Button * button = Button::create(normal, selected);
	button->setPosition(origin+Vec2(x, y));
	button->addClickEventListener(callback);

	return button;
}

