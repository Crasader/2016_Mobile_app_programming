#include "Explain.h"
#include "GameManager.h"

CExplain::CExplain()
{
	b_is_touched = false;
	name_ = "";
	value_ = -1;
}


CExplain::~CExplain()
{
}

bool CExplain::init()
{
	p_img_ = Sprite::create("assemble/explain.png");
	p_img_->setPosition(p_img_->getContentSize() / 2);
	addChild(p_img_);


	//clipping node init
	DrawNode *stencil = DrawNode::create();
	static Point rect[4];
	rect[0] = Point(0, 0);
	rect[1] = Point(834, 0);
	rect[2] = Point(834, 95);
	rect[3] = Point(0, 95);
	Color4F mask(0, 1, 0, 1);
	stencil->drawPolygon(rect, 4, mask, 2, Color4F(0, 0, 0, 1));
	stencil->setPosition(Point(0, 10));

	p_clipping_node_ = ClippingNode::create(stencil);
	addChild(p_clipping_node_);

	 p_label_ = Label::create("", "BM-HANNA.ttf", 20, Size(780, 0));
	p_label_->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	p_label_->setTextColor(Color4B::BLACK);
	p_label_->setPosition(43,  100);
	p_label_->setLineHeight(40);
	p_clipping_node_->addChild(p_label_);

	return true;
}
void CExplain::initWithData(std::string _name, int _value)
{
	Json::Value json = CGameManager::getInstance()->initJson("assemble/explain_info.json");

	if (_name == name_ && _value == value_)
		return;
	name_ = _name;
	value_ = _value;

	std::string text;
	text =  json[_name][_value - 1]["name"].asString() + "\n" +
		 json[_name][_value-1]["price"].asString() + "\n" +
		json[_name][_value-1]["text"].asString();

	p_label_->setPosition(43, 100);
	p_label_->setString(text); 
}

void CExplain::touchBegan(Touch* touch)
{
	if (p_img_->getBoundingBox().containsPoint(touch->getLocation()))
		b_is_touched = true;
	else
		b_is_touched = false;

}
void CExplain::touchMove(Touch* touch)
{
	if (!b_is_touched)// || !p_img_->getBoundingBox().containsPoint(touch->getLocation()))
		return;
	
	Vec2 diff = touch->getLocation() - touch->getPreviousLocation();

	if (95 < p_label_->getContentSize().height && (p_label_->getPositionY() + diff.y > 100 &&
		p_label_->getPositionY() + diff.y < 100 + (p_label_->getContentSize().height - 95)))
	{

		p_label_->setPositionY(p_label_->getPosition().y + diff.y);
	}
}