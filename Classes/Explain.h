#pragma once
#include <cocos2d.h>
USING_NS_CC;

class CExplain : public Node
{
public:
	CExplain();
	~CExplain();


	CREATE_FUNC(CExplain);
	bool										init();
	void										initWithData(std::string _name, int _value);

	void										touchBegan(Touch* touch);
	void										touchMove(Touch* touch);

	ClippingNode*							p_clipping_node_;
	Sprite*									p_img_;
	Label*										p_label_;

	bool										b_is_touched;

	std::string									name_;
	int											value_;

};

