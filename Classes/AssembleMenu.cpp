#include "AssembleMenu.h"
#include "GameManager.h"

CAssembleMenu::CAssembleMenu()
{
//	p_left_menu_ = NULL;
	p_cur_touched_node_ = NULL;
	b_is_selected_ = false;

	str_selected_name_ = "";
	n_selected_idx_ = -1;
	n_selected_value_ = 0;
}


CAssembleMenu::~CAssembleMenu()
{
}

bool CAssembleMenu::init()
{
	Layer::init();
	setContentSize(Size(320, 720));
	
	//menu frame
	auto p_assemble_menu_frame = Sprite::create("assemble/assemble_menu_frame.png");
	p_assemble_menu_frame->setPosition(1120, 360);
	addChild(p_assemble_menu_frame);

	//right side menu
	p_right_menu_ = Menu::create();
	p_right_menu_->setPosition(0, 0);
	addChild(p_right_menu_);

	Json::Value json_right_menu = CGameManager::initJson("assemble/right_menu/path.json");

	if (json_right_menu == NULL)
		return false;

	for (int i = 0; i < json_right_menu["info"].size(); i++)
	{
		MenuItemImage* p_menu;
		
		p_menu = MenuItemImage::create(json_right_menu["info"][i]["path_1"].asString(),
			json_right_menu["info"][i]["path_2"].asString(),json_right_menu["info"][i]["path_3"].asString(),  [=](Ref* _ref){ rightMenuCallBack(dynamic_cast<Node*>(_ref)->getName());});
		p_menu->setScale(0.75f);
		p_menu->setName(json_right_menu["info"][i]["name"].asString());
		p_menu->setPosition(1200, Director::getInstance()->getWinSize().height - p_menu->getContentSize().height * 0.75f / 2 - p_menu->getContentSize().height * 0.75f * i);
		
		p_right_menu_->addChild(p_menu);
	}


	//leftMenu
	p_left_menu_ = CScrollViewLayer::create();
	p_left_menu_->setPosition(Vec2(960, 0));
	p_left_menu_->setContentSize(Size(160, 720));
	addChild(p_left_menu_);
	
	
	return true;
}

void CAssembleMenu::rightMenuCallBack(std::string _name)
{
	p_left_menu_->clear();
	p_cur_touched_node_ = NULL;
	
	str_selected_name_ = _name;
	//left side menu init
	Json::Value json_left_menu = CGameManager::initJson("assemble/left_menu/" + _name + "_info.json");

	for (int i = 0; i < json_left_menu["info"].size(); i++)
	{
		auto p_img = Sprite::create(json_left_menu["info"][i]["path"].asString());
		p_img->setTag(json_left_menu["info"][i]["value"].asInt());
		p_img->setPosition(p_img->getContentSize().width / 2, Director::getInstance()->getWinSize().height - p_img->getContentSize().height / 2 - p_img->getContentSize().height * i);
		p_left_menu_->addObject(p_img);
	}
}

void CAssembleMenu::touchBegan(Touch* _touch)
{
	//left menu touch check
	if (!p_left_menu_->getBoundingBox().containsPoint(_touch->getLocation()))
		return;

	for (int i = 0; i < p_left_menu_->getObjectVector().size(); i++)
	{
		if (p_left_menu_->getObjectVector()[i]->getBoundingBox().containsPoint(p_left_menu_->convertToNodeSpace(_touch->getLocation())))
		{ 
			p_cur_touched_node_ = p_left_menu_->getObjectVector()[i];
			f_time_dt_ = 0;
			n_selected_idx_ = i+1;//
			n_selected_value_ = p_cur_touched_node_->getTag();
			

			DrawNode* p_draw_node = DrawNode::create();
			p_cur_touched_node_->addChild(p_draw_node);
			schedule([=](float dt){
				f_time_dt_ += dt;

				p_draw_node->clear();
				p_draw_node->drawSolidRect(Vec2(0, 0), p_cur_touched_node_->getContentSize(), Color4F(Color4B(92, 255, 75, 125* f_time_dt_)));

				if (f_time_dt_ > 0.5f)			//터치 시간
				{
					//오브젝트 생성해주기!!!!
					b_is_selected_ = true;

					unschedule("touch_schedule");
					p_cur_touched_node_->removeAllChildren();
					p_cur_touched_node_ = NULL;
				}
			}, "touch_schedule");
		}
	}
	p_left_menu_->onTouchBegan(_touch, NULL);
}
void CAssembleMenu::touchMove(Touch* _touch)
{
	p_left_menu_->onTouchMoved(_touch, NULL);
}
void CAssembleMenu::touchEnd(Touch* _touch)
{
	p_left_menu_->onTouchEnded(_touch, NULL);
	unschedule("touch_schedule");
	b_is_selected_ = false;

	if (p_cur_touched_node_)
		p_cur_touched_node_->removeAllChildren();
}
void CAssembleMenu::rightMenuDisable(std::string _name)
{
	auto _menu = p_right_menu_->getChildByName(_name);
	if (_menu)
		dynamic_cast<MenuItemImage*>(_menu)->setEnabled(false);
}
void CAssembleMenu::rightMenuEnable(std::string _name)
{
	auto _menu = p_right_menu_->getChildByName(_name);
	if (_menu)
		dynamic_cast<MenuItemImage*>(_menu)->setEnabled(true);
}