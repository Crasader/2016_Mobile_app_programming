#pragma once
#include <cocos2d.h>

USING_NS_CC;
class CChat : public Node
{
public:
	CChat();
	~CChat();

	CREATE_FUNC(CChat);
	bool															init();
	void															initChat(std::string _name, std::vector<std::string> _chat);

	void															nextChat();
	Sprite*														p_img_;

	std::vector<std::string>										vec_chat_;

	Label*															p_name_;
	Label*															p_label_;

	int																n_current_text_num_;
	int																n_max_text_num_;

	bool															b_chat_end_;
};

