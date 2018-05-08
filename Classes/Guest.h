#pragma once
#include <cocos2d.h>
USING_NS_CC;

enum eGUESTSTATE{
	guest_state_enter,
	guest_state_happy,
	guest_state_upset
};
class CGuest : public Node
{
public:
	CGuest();
	~CGuest();

	CREATE_FUNC(CGuest);

	bool														init();

	void														initWithData(int _level, int _type);

	void														setUpset();

	Sprite*													p_img_;
	eGUESTSTATE											e_guest_state_;
	std::vector<std::string>									vec_enter_text_;
	std::vector<std::string>									vec_happy_text_;
	std::vector<std::string>									vec_upset_text_;

	int															n_reward_;
	std::string													str_name_;
	std::string													str_type_;


};

