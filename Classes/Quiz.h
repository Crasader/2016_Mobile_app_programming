#pragma once
#include <cocos2d.h>
#include "json/json.h"
#include "Chat.h"
#include "Guest.h"

USING_NS_CC;
class CQuiz : public Layer
{
public:
	CQuiz();
	~CQuiz();

	CREATE_FUNC(CQuiz);

	bool								init();

	void								initStage();

	int									n_count_;

	Json::Value						j_val_;
	CChat*							p_chat_;
	CGuest*							p_guest_;

	std::vector<MenuItemFont*>	vec_menu_;
	Menu*							p_menu_;
	std::vector<int>					vec_answer_;
};

