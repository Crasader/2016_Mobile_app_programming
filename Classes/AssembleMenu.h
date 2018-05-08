#pragma once
#include <cocos2d.h>
#include "ScrollViewLayer.h"
USING_NS_CC;

class CAssembleMenu : public Layer
{
public:
	CAssembleMenu();
	~CAssembleMenu();

	CREATE_FUNC(CAssembleMenu);
	bool								init();
	void								rightMenuCallBack(std::string _name);
	void								rightMenuDisable(std::string _name);
	void								rightMenuEnable(std::string _name);

	void								touchBegan(Touch* _touch);
	void								touchMove(Touch* _touch);
	void								touchEnd(Touch* _touch);

	CScrollViewLayer*				p_left_menu_;

	float								f_time_dt_;
	Node*								p_cur_touched_node_;


	bool								b_is_selected_;
	std::string							str_selected_name_;
	int									n_selected_value_;
	int									n_selected_idx_;
	Menu*							p_right_menu_;
};

