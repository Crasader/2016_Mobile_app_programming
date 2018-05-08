#include "Intro.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "UILayer.h"
CIntro::CIntro()
{
}


CIntro::~CIntro()
{
}

bool CIntro::init()
{
	
	auto bg = Sprite::create("logo.png");
	bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2) - Vec2(0, 70));
	bg->setOpacity(0);
	addChild(bg);
	
	CSoundManager::getInstance()->playSfx("sound/logo.mp3");
	bg->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f),FadeOut::create(1.0f), CallFunc::create([=](){
		/*CSoundManager::getInstance()->preloadSfx("sound/assemble_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/attach.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/correct.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/detach.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/ending_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/gauge.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/gauge_2.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/logo.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/spray.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/stage_1_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/stage_2_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/stage_3_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/stage_4_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/title_bgm.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/wrong.mp3");
		CSoundManager::getInstance()->preloadSfx("sound/wrong_bgm.mp3");*/


		CGameManager::getInstance()->changeState(e_state_title);
	}), NULL));
	bg->runAction(MoveBy::create(0.8f, Vec2(0, 70)));

	CUILayer::getInstance()->setVisible(false);
	return true;
}