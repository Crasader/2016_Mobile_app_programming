#include "Ending.h"
#include "GameManager.h"
#include "UILayer.h"
CEnding::CEnding()
{
}


CEnding::~CEnding()
{
}

bool CEnding::init()
{
	
	auto bg = Sprite::create("ending.png");
	bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2) - Vec2(0, 70));
	bg->setOpacity(0);
	addChild(bg);
	
	CGameManager::getInstance()->reGame();

	CUILayer::getInstance()->updateLevel();
	CUILayer::getInstance()->updateMoney();

	CUILayer::getInstance()->setVisible(false);
	//CSoundManager::getInstance()->playSfx("sound/logo.mp3");
	bg->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f),FadeOut::create(1.0f), CallFunc::create([=](){
		CGameManager::getInstance()->changeState(e_state_title);
	}), NULL));
	bg->runAction(MoveBy::create(0.8f, Vec2(0, 70)));
	return true;
}