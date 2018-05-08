#include "HelloWorldScene.h"
#include "GameManager.h"
#include "UILayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	CGameManager::getInstance()->init();
	CGameManager::getInstance()->changeState(e_state_intro, false);
	addChild(CGameManager::getInstance()->getLayer());

	CUILayer::getInstance()->init();
	CGameManager::getInstance()->getLayer()->addChild(CUILayer::getInstance()->p_layer_, 10);

    
    return true;
}
