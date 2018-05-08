#include "UILayer.h"
#include "GameManager.h"

CUILayer::CUILayer()
{
}


CUILayer::~CUILayer()
{
}

bool CUILayer::init()
{
	p_layer_ = Layer::create();

	p_layer_->retain();

	auto bg = Sprite::create("ui_bar.png");
	bg->setPosition(bg->getContentSize().width / 2, 720 - bg->getContentSize().height / 2);
	p_layer_->addChild(bg);


	p_money_label_ = Label::create("", "BM-HANNA.ttf", 35);
	p_money_label_->setPosition(605, 720 - 43);
	p_money_label_->setTextColor(Color4B::BLACK);
	p_money_label_->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	p_layer_->addChild(p_money_label_);

	p_level_label_ = Label::create("", "BM-HANNA.ttf", 35);
	p_level_label_->setPosition(76, 720 - 43);
	p_level_label_->setTextColor(Color4B::BLACK);
	p_level_label_->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	p_layer_->addChild(p_level_label_);

	Sprite* p_sprite = Sprite::create("gauge.png");
	p_progress_ = ProgressTimer::create(p_sprite);
	p_progress_->setType(ProgressTimer::Type::BAR);
	p_progress_->setPosition(262, 720 - 47);
	p_progress_->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	p_progress_->setPercentage(0);
	p_progress_->setBarChangeRate(Vec2(1, 0));
	p_progress_->setMidpoint(Vec2(0, 0.5f));
	p_layer_->addChild(p_progress_);

	updateMoney();
	updateLevel();

	setVisible(false);

	return true;
}
CUILayer* CUILayer::getInstance()
{
	static CUILayer s_ui_layer_;
	return &s_ui_layer_;
}

void CUILayer::updateMoney()
{
	char str[64];
	util_add_comma_to_num(StringUtils::toString(CGameManager::getInstance()->n_money_).c_str(), str, 64);
	p_money_label_->setString(str);

	if (CGameManager::getInstance()->n_level_ == 1)
	{
		p_progress_->runAction(ProgressTo::create(0.5f, CGameManager::getInstance()->n_money_ / 1000000.f * 100));
	}
	else if (CGameManager::getInstance()->n_level_ == 4)
	{
		p_progress_->setPercentage(100);
	}
	else
	{
		p_progress_->runAction(ProgressTo::create(0.5f, (CGameManager::getInstance()->n_money_ - (CGameManager::getInstance()->n_level_ - 1) * 1000000) / 1000000.f * 100));
	}
}
void CUILayer::updateLevel()
{
	p_level_label_->setString(StringUtils::toString(CGameManager::getInstance()->n_level_));


	if (CGameManager::getInstance()->n_level_ == 1)
	{
		p_progress_->runAction(ProgressTo::create(0.5f, CGameManager::getInstance()->n_money_ / 1000000.f * 100));
	}
	else if (CGameManager::getInstance()->n_level_ == 4)
	{
		p_progress_->setPercentage(100);
	}
	else
	{
		p_progress_->runAction(ProgressTo::create(0.5f, (CGameManager::getInstance()->n_money_ - (CGameManager::getInstance()->n_level_ - 1) * 1000000) / 1000000.f * 100));
	}
}
void CUILayer::textEffect(std::string _txt, int size, Vec2 pos, Color4B color, float _time)
{
	Label* p_label = Label::create(_txt, "BM-HANNA.ttf", size);

	p_label->setPosition(pos);

	p_label->setTextColor(color);

	p_label->runAction(Sequence::create(MoveBy::create(_time*0.25f, Vec2(0, 15)),Spawn::create(MoveBy::create(_time*0.75f, Vec2(0, 30)), FadeOut::create(0.7f), NULL), RemoveSelf::create(), NULL));
	p_layer_->addChild(p_label);
}