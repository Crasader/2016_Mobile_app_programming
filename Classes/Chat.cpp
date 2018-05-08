#include "Chat.h"


CChat::CChat()
{
	b_chat_end_ = false;

	n_current_text_num_ = 0;
}


CChat::~CChat()
{
}

bool CChat::init()
{
	p_img_ = Sprite::create("room/chat.png");
	p_img_->setPosition(Director::getInstance()->getWinSize().width / 2, p_img_->getContentSize().height / 2);
	addChild(p_img_);
	return true;
}

void CChat::initChat(std::string _name, std::vector<std::string> _chat)
{
	vec_chat_ = _chat;

	p_name_ = Label::create(_name, "BareunBatangOTFM.otf", 30, Size(1000, 0));
	p_name_->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	p_name_->setPosition(33, 720 - 540);
	p_name_->enableOutline(Color4B::BLACK, 2);
	addChild(p_name_);


	p_label_ = Label::create(vec_chat_[n_current_text_num_], "BareunBatangOTFM.otf", 30, Size(1000, 0));
	p_label_->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	p_label_->setPosition(34, 720-578);
	p_label_->enableOutline(Color4B::BLACK, 2	);
	addChild(p_label_);

	n_max_text_num_ = vec_chat_.size();
}

void CChat::nextChat()
{
	if (n_current_text_num_ + 1 < n_max_text_num_)
		p_label_->setString(vec_chat_[++n_current_text_num_]);
	else
		b_chat_end_ = true;
}