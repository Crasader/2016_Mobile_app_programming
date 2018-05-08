#include "Guest.h"
#include "GameManager.h"

CGuest::CGuest()
{
}


CGuest::~CGuest()
{
}

bool CGuest::init()
{
	e_guest_state_ = guest_state_enter;
	return true;
}
void CGuest::initWithData(int _level, int _type)
{
	Json::Value json = CGameManager::getInstance()->initJson("room/guest/guest_info_" + StringUtils::toString(_level) + ".json");

	p_img_ = Sprite::create(json["info"][_type]["img_path"].asString());

	p_img_->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	p_img_->setPosition(974, 720 - 490);
	addChild(p_img_);

	str_name_ = json["info"][_type]["name"].asString();
	str_type_ = json["info"][_type]["type"].asString();

	for (int i = 0; i < json["info"][_type]["enter_text"].size(); i++)
	{
		vec_enter_text_.push_back(json["info"][_type]["enter_text"][i].asString());
	}

	for (int i = 0; i < json["info"][_type]["happy_text"].size(); i++)
	{
		vec_happy_text_.push_back(json["info"][_type]["happy_text"][i].asString());
	}

	for (int i = 0; i < json["info"][_type]["upset_text"].size(); i++)
	{
		vec_upset_text_.push_back(json["info"][_type]["upset_text"][i].asString());
	}

	CGameManager::getInstance()->n_cpu_score_ = json["info"][_type]["cpu_score"].asInt();
	CGameManager::getInstance()->n_ram_score_ = json["info"][_type]["ram_score"].asInt();
	CGameManager::getInstance()->n_vga_score_ = json["info"][_type]["vga_score"].asInt();
	CGameManager::getInstance()->n_power_score_ = json["info"][_type]["power_score"].asInt();
	CGameManager::getInstance()->n_storage_score_ = json["info"][_type]["storage_score"].asInt();

	n_reward_ = json["info"][_type]["reward"].asInt();
	
}

void CGuest::setUpset()
{
	auto img = Sprite::create("room/guest/upset.png");
	img->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	img->setPosition(974, 720 - 490);
	addChild(img);
}