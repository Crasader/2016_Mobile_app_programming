#include "Clean.h"
#include "GameManager.h"
#include "SoundManager.h"
#define MAX_DUST_ACCEL 3.0f

CClean::CClean()
{
	b_blow_ = false;
	b_touched_ = false;
}


CClean::~CClean()
{
}

bool CClean::init()
{
	CSoundManager::getInstance()->preloadSfx("sound/gauge_2.mp3");
	CSoundManager::getInstance()->preloadSfx("sound/spray.mp3");
	startCleanSetting();

	//bgpng
	auto p_bg = Sprite::create("assemble/bg.png");
	p_bg->setPosition(Director::getInstance()->getWinSize() / 2);
	addChild(p_bg);

	auto p_board = Sprite::create("clean/board.png");
	p_board->setPosition(640, 300);
	addChild(p_board);

	for (int i = 0; i < 200; i++)
	{
		CDust* p_dust = CDust::create();
		addChild(p_dust);
		vec_dust_.push_back(p_dust);
	}
	pt_pos_ = Vec2(800, 400);
	p_spray = Sprite::create("clean/spray.png");
	p_spray->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	p_spray->setPosition(pt_pos_);
	p_spray->setRotation(30);
	addChild(p_spray, 1);

	p_button_ = Sprite::create("clean/button_1.png");
	//p_button_->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	p_button_->setPosition(123, 80);
	addChild(p_button_);

	p_blow_ = Sprite::create("clean/blow.png");
	p_blow_->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	p_blow_->setVisible(b_blow_);
	addChild(p_blow_);
	

	schedule([=](...){
		Vec2 move = Vec2(getDeviceXRotation() * 0.3f, getDeviceYRotation() * 0.3f);

		Rect col = Rect(300, 102, 698 + 60, 466 + 80);
		if (col.containsPoint(pt_pos_ + move))
			pt_pos_ += move;
		p_spray->setPosition(pt_pos_);
		p_blow_->setPosition(pt_pos_ - Vec2(10, 22));
		p_blow_->setVisible(b_blow_);

		float level = getMicLevel();
		if (level > 20000)
			b_blow_ = true;
		else if (!b_touched_ && level < 20000)
			b_blow_ = false;



		if (abs(getDeviceAccel()) > 20 && f_gauge_ < 100)
		{
			if (!b_is_playing_shake_)
			{
				b_is_playing_shake_ = true;
			
				if (n_shake_id_ != -1)
					CSoundManager::getInstance()->stopSfx(n_shake_id_);

				n_shake_id_ = CSoundManager::getInstance()->playSfx("sound/gauge_2.mp3"); 
				scheduleOnce([=](...){ b_is_playing_shake_ = false; CSoundManager::getInstance()->stopSfx(n_shake_id_);  n_shake_id_ = -1;  }, 0.25f, "gauge_sound");
			}
			
			f_gauge_ += 5.f;
			//p_progress_->stopAllActions();
			//p_progress_->runAction(ProgressTo::create(0.1f, f_gauge_));
			p_progress_->setPercentage(f_gauge_);

			//return;
		}
		/*else if(
		{
			if (n_shake_id_ != -1)
				CSoundManager::getInstance()->stopSfx(n_shake_id_);
			n_shake_id_ = -1;
			b_is_playing_shake_ = false;
		}*/

		if (b_blow_ && f_gauge_ > 0)
		{
			
			if (n_shake_id_ != -1)
				CSoundManager::getInstance()->stopSfx(n_shake_id_);
			n_shake_id_ = -1;
			b_is_playing_shake_ = false;


			if (!b_is_playing_spray_)
			{
				b_is_playing_spray_ = true;

				if (n_spray_id_ != -1)
					CSoundManager::getInstance()->stopSfx(n_spray_id_);

				n_spray_id_ = CSoundManager::getInstance()->playSfx("sound/spray.mp3");
				scheduleOnce([=](...){ b_is_playing_spray_ = false; CSoundManager::getInstance()->stopSfx(n_spray_id_);  n_spray_id_ = -1;  }, 10.5f, "spray_sound");
			}

			p_blow_->setVisible(true);

			f_gauge_ -= 0.3f;
			//p_progress_->stopAllActions();
			p_progress_->setPercentage(f_gauge_);
			//p_progress_->runAction(ProgressTo::create(0.1f, f_gauge_));
			for (CDust* p_dust : vec_dust_)
			{
				if (p_dust->getPosition().distance(pt_pos_) < 80)
					p_dust->blow(pt_pos_);
			}
		}
		else
		{

			if (n_spray_id_ != -1)
				CSoundManager::getInstance()->stopSfx(n_spray_id_);
			n_spray_id_ = -1;
			b_is_playing_spray_ = false;
		}
		if (f_gauge_ <= 0)
			p_blow_->setVisible(false);

		for (int i = 0; i < vec_dust_.size(); i++)
		{
			if (vec_dust_[i]->f_life_ <= 0)
			{
				vec_dust_[i]->removeFromParent();
				vec_dust_.erase(vec_dust_.begin() + i);
				i--;
			}
		}



		if (vec_dust_.size() < 20)
			p_complete_->setEnabled(true);
	}, "pulse");

	initTouch();

	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	addChild(menu);

	p_complete_ = MenuItemImage::create("assemble/complete_1.png", "assemble/complete_2.png", "assemble/complete_3.png", [=](...){
		
		CGameManager::getInstance()->b_is_result_ = true;
		CGameManager::getInstance()->b_is_success_ = true;

		endCleanSetting();

		CGameManager::getInstance()->changeState(e_state_room);
	});
	p_complete_->setPosition(905, 720 - p_complete_->getContentSize().height / 4);
	p_complete_->setEnabled(false);
	menu->addChild(p_complete_);

	f_gauge_ = 0;

	Sprite* p_sprite = Sprite::create("clean/gauge.png");
	p_progress_ = ProgressTimer::create(p_sprite);
	p_progress_->setType(ProgressTimer::Type::BAR);
	p_progress_->setPosition(123, 720 - 300);
	p_progress_->setRotation(-90);
	p_progress_->setPercentage(f_gauge_);
	p_progress_->setBarChangeRate(Vec2(1, 0));
	p_progress_->setMidpoint(Vec2(0, 0.5f));
	addChild(p_progress_);

	auto frame = Sprite::create("clean/gauge_frame.png");
	frame->setPosition(123, 720 - 300);
	frame->setRotation(-90);
	addChild(frame);


	return true;
}
void CClean::initTouch()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CClean::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CClean::onTouchMoved, this); //[=](Touch* touch, Event* _event){};
	listener->onTouchEnded = CC_CALLBACK_2(CClean::onTouchEnded, this); //[=](Touch*, Event*){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
bool CClean::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (p_button_->getBoundingBox().containsPoint(touch->getLocation()) && f_gauge_ > 0)
	{
		p_button_->setTexture("clean/button_2.png");
		b_blow_ = true;
		b_touched_ = true;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	for (CDust* p_dust : vec_dust_)
	{
		if (p_dust->getPosition().distance(touch->getLocation()) < 80)
			p_dust->blow(touch->getLocation());
	}

	f_gauge_ += 10;
	p_progress_->stopAllActions();
	p_progress_->runAction(ProgressTo::create(0.3f, f_gauge_));
#endif
	return true;
}
void CClean::onTouchMoved(Touch* touch, Event* _event)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	for (CDust* p_dust : vec_dust_)
	{
		if (p_dust->getPosition().distance(touch->getLocation()) < 80)
			p_dust->blow(touch->getLocation());
	}
#endif
}
void CClean::onTouchEnded(Touch* touch, Event* _event)
{
	p_button_->setTexture("clean/button_1.png");
	b_blow_ = false;
	b_touched_ = false;
}

bool CDust::init()
{
	initWithFile("clean/dust_1.png");
	setPosition(330 + rand() % 698, 142 + rand() % 466);
	setRotation(rand() % 360);

	f_accel = 0.0f;
	f_life_ = 100;
	f_degree_ = 0;

	Rect col = Rect(330, 142, 698, 466);
	schedule([=](...){
		if (f_accel <= 0)
		{
			f_accel = 0;
			return;
		}
		if (f_life_ <= 0)
		{
			f_life_ = 0;
			setOpacity(0);
			unschedule("pulse");
			return;
		}
		if (!col.containsPoint(getPosition()) && f_life_ != 0)
		{
			f_life_ = 0;
			runAction(FadeOut::create(0.1f));
			unschedule("pulse");
			return;
		}
		Vec2 move = Vec2(cos(f_degree_) * f_accel *2, sin(f_degree_) * f_accel *2);

		setPosition(getPosition() + move);
		setRotation(getRotation() + 5.f);

		f_accel -= 0.1f;
		f_life_ -= 0.9f;

		if (f_life_ <= 0)
			f_life_ = 0;

		setOpacity(255 * f_life_ / 100.f);
	}, "pulse");
	return true;
}
void CDust::blow(Vec2 _pos)
{
	f_accel = MAX_DUST_ACCEL;

	f_degree_ = GetAngle(_pos, getPosition());

}