#pragma once
#include <cocos2d.h>
USING_NS_CC;

class CUILayer 
{
public:
	CUILayer();
	~CUILayer();

	bool										init();

	static CUILayer*					getInstance();

	Layer*								p_layer_;
	void								updateMoney();
	void								updateLevel();

	Label*								p_money_label_;
	Label*								p_level_label_;
	ProgressTimer*					p_progress_;
	void								textEffect(std::string _txt, int size, Vec2 pos, Color4B color, float _time = 0.7f);
	void								setVisible(bool _visible){ if(p_layer_)p_layer_->setVisible(_visible); }



};

