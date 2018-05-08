#pragma once
#include <cocos2d.h>
USING_NS_CC;


class CDust : public Sprite
{
public:
	CDust(){}
	~CDust(){ }

	CREATE_FUNC(CDust);
	bool									init();

	void									blow(Vec2 _pos);


	float									f_accel;
	float									f_life_;
	float									f_degree_;
};


class CClean : public Layer
{
public:
	CClean();
	~CClean();

	CREATE_FUNC(CClean);

	bool											init();

	void initTouch();
	bool onTouchBegan(Touch* touch, Event* unused_event);
	void onTouchMoved(Touch* touch, Event* _event);
	void onTouchEnded(Touch* touch, Event* _event);

	std::vector<CDust*>							vec_dust_;

	Vec2											pt_pos_;
	Sprite*										p_spray;
	Sprite*										p_button_;
	Sprite*										p_blow_;
	bool											b_blow_;

	bool											b_touched_;

	MenuItemImage*							p_complete_;

	ProgressTimer*								p_progress_;

	float											f_gauge_;
	bool											b_is_playing_shake_ = false;
	bool											b_is_playing_spray_ = false;

	int												n_shake_id_ = -1;
	int												n_spray_id_ = -1;
};
