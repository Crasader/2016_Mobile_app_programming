#include "Room.h"
#include "GameManager.h"
#include "UILayer.h"
#include "SoundManager.h"
CRoom::CRoom()
{
	p_guest_ = NULL;
	p_chat_ = NULL;
}


CRoom::~CRoom()
{
}

bool CRoom::init()
{
	CUILayer::getInstance()->setVisible(true);
	/* bg init */
	p_bg_ = Sprite::create("room/bg_" +  StringUtils::toString(CGameManager::getInstance()->n_level_) + ".png");
	p_bg_->setPosition(Director::getInstance()->getWinSize() / 2);
	addChild(p_bg_);


	
	if (!CGameManager::getInstance()->b_is_result_)
	{
		CSoundManager::getInstance()->playBGM("sound/stage_" + StringUtils::toString(CGameManager::getInstance()->n_level_) + "_bgm.mp3");

		waitGuest();
		
	}
	else
	{
		showResult();
		
	}
	initTouch();



	return true;
}

void CRoom::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* _event){

		if (!p_chat_)
			return true;
		if (p_chat_->p_img_->getBoundingBox().containsPoint(touch->getLocation()))
			p_chat_->nextChat();

		if (p_chat_->b_chat_end_)
		{
			if (!CGameManager::getInstance()->b_is_result_)
			{
				CSoundManager::getInstance()->FadeBGM("sound/assemble_bgm.mp3");
				if (p_guest_->str_type_ == "clean")
					CGameManager::getInstance()->changeState(e_state_clean);
				else if (p_guest_->str_type_ == "reassemble")
					CGameManager::getInstance()->changeState(e_state_reassemble);
				else if (p_guest_->str_type_ == "quiz")
					CGameManager::getInstance()->changeState(e_state_quiz);
				else
					CGameManager::getInstance()->changeState(e_state_assemble);

				listener->setEnabled(false);
			}
			else
			{
				
				CGameManager::getInstance()->b_is_result_ = false;

				if (!CGameManager::getInstance()->b_is_success_)
					CSoundManager::getInstance()->FadeBGM("sound/stage_" + StringUtils::toString(CGameManager::getInstance()->n_level_) + "_bgm.mp3");

				p_guest_->removeFromParent();
				p_guest_ = NULL;

				p_chat_->removeFromParent();
				p_chat_ = NULL;
				//µ· °è»ê

				int n_cur_level = CGameManager::getInstance()->n_level_;
				if (CGameManager::getInstance()->nextStage())
				{
					if (n_cur_level < CGameManager::getInstance()->n_level_)
					{
						CSoundManager::getInstance()->FadeBGM("sound/stage_" + StringUtils::toString(CGameManager::getInstance()->n_level_) + "_bgm.mp3");

						CUILayer::getInstance()->textEffect("LEVEL UP", 100, Vec2(640, 360), Color4B::ORANGE, 1.5f);

						CUILayer::getInstance()->updateLevel();
						p_bg_->runAction(Sequence::create(DelayTime::create(1.5f), FadeOut::create(1.0f), RemoveSelf::create(), NULL));
						p_bg_ = Sprite::create("room/bg_" + StringUtils::toString(CGameManager::getInstance()->n_level_) + ".png");
						p_bg_->setPosition(Director::getInstance()->getWinSize() / 2);
						p_bg_->setOpacity(0);
						p_bg_->runAction(Sequence::create(DelayTime::create(1.5f), FadeIn::create(1.0f), NULL));
						addChild(p_bg_);


					}
					waitGuest();
				}
				else
					ending();

			}
		}

		return true;
	};
	//listener->onTouchMoved = CC_CALLBACK_2(CAssemble::onTouchMoved, this); //[=](Touch* touch, Event* _event){};
	//listener->onTouchEnded = CC_CALLBACK_2(CAssemble::onTouchEnded, this); //[=](Touch*, Event*){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void CRoom::waitGuest()
{
	scheduleOnce([=](...){
		p_guest_ = CGuest::create();
		p_guest_->initWithData(CGameManager::getInstance()->n_level_, CGameManager::getInstance()->n_type_);
		addChild(p_guest_);

		p_chat_ = CChat::create();
		p_chat_->initChat(p_guest_->str_name_,p_guest_->vec_enter_text_);
		addChild(p_chat_);
	}, 2.3f, "wait_guest");
}
void CRoom::showResult()
{
	p_guest_ = CGuest::create();
	p_guest_->initWithData(CGameManager::getInstance()->n_level_, CGameManager::getInstance()->n_type_);

	addChild(p_guest_);

	p_chat_ = CChat::create();
	if (CGameManager::getInstance()->b_is_success_)
	{
		

		if (CGameManager::getInstance()->n_level_ == 4 && CGameManager::getInstance()->n_count_ >= 3)
			CSoundManager::getInstance()->playBGM("sound/ending_bgm.mp3");
		else
			CSoundManager::getInstance()->FadeBGM("sound/stage_" + StringUtils::toString(CGameManager::getInstance()->n_level_) + "_bgm.mp3");

		p_chat_->initChat(p_guest_->str_name_, p_guest_->vec_happy_text_);
		int n_reward = p_guest_->n_reward_;
		CGameManager::getInstance()->n_money_ += n_reward;
	
		scheduleOnce([=](...){
			
			CUILayer::getInstance()->updateMoney();
			char str[64];
			util_add_comma_to_num(StringUtils::toString(n_reward).c_str(), str, 64);
			CUILayer::getInstance()->textEffect("+" + StringUtils::toString(str), 30, Vec2(667, 720 - 60), Color4B::RED);
		}, 2.0f, "money_add");
		
	}
	else
	{
		p_chat_->initChat(p_guest_->str_name_, p_guest_->vec_upset_text_);
		p_guest_->setUpset();
		CSoundManager::getInstance()->FadeBGM("sound/wrong_bgm.mp3", false);
	}
	addChild(p_chat_);
}

void CRoom::ending()
{
	CGameManager::getInstance()->changeState(e_state_ending);
}