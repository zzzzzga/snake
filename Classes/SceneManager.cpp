#include "SceneManager.h"
#include "LoadLayer.h"
#include "MainLayer.h"

void SceneManager::createLoadScene()
{
	loadScene = Scene::create();
	LoadLayer* loadLayer = LoadLayer::create();
	loadLayer->tsm = this;
	loadScene->addChild(loadLayer);

	Director::getInstance()->runWithScene(loadScene);
}

void SceneManager::goMainScene()
{
	mainScene = Scene::create();
	MainLayer* mainLayer = MainLayer::create();
	mainScene->addChild(mainLayer);

	TransitionFade * tranScene = TransitionFade::create(0.6f, mainScene);
	Director::getInstance()->replaceScene(tranScene);
}