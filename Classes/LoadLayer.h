#ifndef _LOADLAYER_H_
#define _LOADLAYER_H_

#include <iostream>
#include "cocos2d.h"
#include "SceneManager.h"
#include "ui/CocosGUI.h"
using namespace ui;
USING_NS_CC;
class LoadLayer:public Layer
{
public:
	CREATE_FUNC(LoadLayer);
	virtual bool init();

	Button* createButton(const char * normal, const char * selected, float x, float y, const Widget::ccWidgetClickCallback& callback);
	void startGame(Ref* pSender);
	void optionCallBack(Ref* pSender);
	void questionCallBack(Ref * pSender);
	void exitCallBack(Ref * pSender);

public:
	SceneManager * tsm;

};

#endif