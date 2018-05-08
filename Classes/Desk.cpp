#include "Desk.h"
#include "GameManager.h"
#include "UILayer.h"
#include "SoundManager.h"

CDesk::CDesk()
{
	p_cur_delete_comp_ = NULL;
}


CDesk::~CDesk()
{
}

bool CDesk::init()
{
	auto p_bg = Sprite::create("assemble/desk.png");
	p_bg->setPosition(475, 720 - 230);
	addChild(p_bg);

	e_make_step_ = e_step_one;

	p_draw_node_ = DrawNode::create();
	p_draw_node_->setPosition(0, 0);
	addChild(p_draw_node_, 10);

	positionInit();
	return true;
}
void CDesk::positionInit()
{
	
	vec_position_main_board_ = { { { 131, 720 - 564, 696, 500 }, false } };
	vec_position_cpu_ = { { { 640, 720 - 330, 91, 91}, false } };
	vec_position_ram_ = { { { 453, 720 - 429, 319, 17}, false },
	{ { 453, 720 - 449, 319, 17 }, false },
	{ { 453, 720 - 484, 319, 17 }, false },
	{ { 453, 720 - 504, 319, 17 }, false } };
	vec_position_power_ = { { { 463, 720 - 525 -314, 268, 314}, false } };
	vec_position_vga_ = { { { 56, 720 - 434, 358, 271}, false } };
	vec_position_storage_ = { { { 262, 720 - 442, 105, 36}, false },
	{ { 262, 720 - 482, 105, 36 }, false },
	{ { 140, 720 - 442, 105, 36 }, false },
	{ { 140, 720 - 482, 105, 36 }, false } };
}

void CDesk::ready(CComponent* _comp)
{
	switch (e_make_step_)
	{
	case e_step_one:
		p_draw_node_->drawSolidRect(vec_position_main_board_[0]._rt.origin, vec_position_main_board_[0]._rt.origin + vec_position_main_board_[0]._rt.size, Color4F(Color4B(255, 0, 0, 125)));
		break;
	case e_step_two:
	{
		switch (_comp->getComponentType())
		{
		case component_type_cpu:
			for (int i = 0; i < vec_position_cpu_.size(); i++)
			{
				if (!vec_position_cpu_[i]._used)
					p_draw_node_->drawSolidRect(vec_position_cpu_[i]._rt.origin, vec_position_cpu_[i]._rt.origin + vec_position_cpu_[i]._rt.size, Color4F(Color4B(255, 0, 0, 125)));
			}
			break;

		case component_type_ram :
			for (int i = 0; i < vec_position_ram_.size(); i++)
			{
				if (!vec_position_ram_[i]._used)
					p_draw_node_->drawSolidRect(vec_position_ram_[i]._rt.origin, vec_position_ram_[i]._rt.origin + vec_position_ram_[i]._rt.size, Color4F(Color4B(255, 0, 0, 125)));
			}
			break;

		case component_type_power:
			for (int i = 0; i < vec_position_power_.size(); i++)
			{
				if (!vec_position_power_[i]._used)
					p_draw_node_->drawSolidRect(vec_position_power_[i]._rt.origin, vec_position_power_[i]._rt.origin + vec_position_power_[i]._rt.size, Color4F(Color4B(255, 0, 0, 125)));
			}
			break;

		case component_type_vga:
			for (int i = 0; i < vec_position_vga_.size(); i++)
			{
				if (!vec_position_vga_[i]._used)
					p_draw_node_->drawSolidRect(vec_position_vga_[i]._rt.origin, vec_position_vga_[i]._rt.origin + vec_position_vga_[i]._rt.size, Color4F(Color4B(255, 0, 0, 125)));
			}
			break;

		case component_type_storage:
			for (int i = 0; i < vec_position_storage_.size(); i++)
			{
				if (!vec_position_storage_[i]._used)
					p_draw_node_->drawSolidRect(vec_position_storage_[i]._rt.origin, vec_position_storage_[i]._rt.origin + vec_position_storage_[i]._rt.size, Color4F(Color4B(255, 0, 0, 125)));
			}
			break;


		default:
			break;
		}
		break;
	}
	case e_step_three:
		break;
	case e_step_finish:
		break;
	default:
		break;
	}
}
void CDesk::compMove(CComponent* _comp, Vec2 _pos, bool _forced )
{
	Rect rt;
	switch (e_make_step_)
	{
	case e_step_one:
		rt = vec_position_main_board_[0]._rt;
		if (_forced || rt.containsPoint(_pos))
			_comp->setPosition(rt.getMidX(), rt.getMidY());
		
		break;
	case e_step_two:
	{
		switch (_comp->getComponentType())
		{
		case component_type_cpu:
			for (int i = 0; i < vec_position_cpu_.size(); i++)
			{
				rt = vec_position_cpu_[i]._rt;
				if (_forced || !vec_position_cpu_[i]._used && rt.containsPoint(_pos))
				{
					_comp->setPosition(rt.getMidX(), rt.getMidY());
					break;
				}
			}
			break;

		case component_type_ram:
			for (int i = 0; i < vec_position_ram_.size(); i++)
			{
				rt = vec_position_ram_[i]._rt;
				if (!vec_position_ram_[i]._used && (rt.containsPoint(_pos)|| _forced))
				{
					_comp->setPosition(rt.getMidX(), rt.getMidY());
					break;
				}
			}
			break;

		case component_type_power:
			for (int i = 0; i < vec_position_power_.size(); i++)
			{
				rt = vec_position_power_[i]._rt;
				if (_forced||!vec_position_power_[i]._used && rt.containsPoint(_pos))
					_comp->setPosition(rt.getMidX(), rt.getMidY());
			}
			break;
		case component_type_vga:
			for (int i = 0; i < vec_position_vga_.size(); i++)
			{
				rt = vec_position_vga_[i]._rt;
				if (_forced||!vec_position_vga_[i]._used && rt.containsPoint(_pos))
					_comp->setPosition(rt.getMidX(), rt.getMidY());
			}
			break;
		case component_type_storage:
			for (int i = 0; i < vec_position_storage_.size(); i++)
			{
				rt = vec_position_storage_[i]._rt;
				if ( !vec_position_storage_[i]._used && (rt.containsPoint(_pos) || _forced))
				{
					_comp->setPosition(rt.getMidX(), rt.getMidY());
					break;
				}
			}
			break;
		default:
			break;
		}
		break;
	}
	case e_step_three:
		break;
	case e_step_finish:
		break;
	}
}
bool CDesk::attach(CComponent* _comp, bool _forced)
{
	//check and attach or drop
	p_draw_node_->clear();

	bool b_col = _forced;
	
	
	switch (_comp->getComponentType())
	{
	case component_type_mainboard:
		if (_forced || vec_position_main_board_[0]._rt.containsPoint(_comp->getPosition()))
		{
			vec_position_main_board_[0]._used = true;
			_comp->n_slot_idx_ = 0;
			b_col = true;
			e_make_step_ = e_step_two;
		}
		else
		{
			//삭제기능..
			for (int i = 0; i < vec_component_.size(); i++)
				vec_component_[i]->removeFromParent();
			vec_component_.clear();

			for (int i = 0; i < vec_position_main_board_.size(); i++)
				vec_position_main_board_[i]._used = false;

			for (int i = 0; i < vec_position_cpu_.size(); i++)
				vec_position_cpu_[i]._used = false;

			for (int i = 0; i < vec_position_ram_.size(); i++)
				vec_position_ram_[i]._used = false;

			for (int i = 0; i < vec_position_storage_.size(); i++)
				vec_position_storage_[i]._used = false;

			for (int i = 0; i < vec_position_vga_.size(); i++)
				vec_position_vga_[i]._used = false;

			for (int i = 0; i < vec_position_power_.size(); i++)
				vec_position_power_[i]._used = false;

		}
		
		break;
	case component_type_cpu:
		for (int i = 0; i < vec_position_cpu_.size(); i++)
		{
			if (_forced || !vec_position_cpu_[i]._used && vec_position_cpu_[i]._rt.containsPoint(_comp->getPosition()))
			{
				vec_position_cpu_[i]._used = true;
				b_col = true;
				_comp->n_slot_idx_ = i;
				break;
			}
		}
		break;

	case component_type_ram:
		for (int i = 0; i < vec_position_ram_.size(); i++)
		{
			if (!vec_position_ram_[i]._used && (_forced || vec_position_ram_[i]._rt.containsPoint(_comp->getPosition())))
			{
				vec_position_ram_[i]._used = true;
				b_col = true;
				_comp->n_slot_idx_ = i;
				break;
			}
				
		}
		break;


	case component_type_power:
		for (int i = 0; i < vec_position_power_.size(); i++)
		{
			if (_forced || !vec_position_power_[i]._used  && vec_position_power_[i]._rt.containsPoint(_comp->getPosition()))
			{
				vec_position_power_[i]._used = true;
				b_col = true;
				_comp->n_slot_idx_ = i;
				break;
			}

		}
		break;

	case component_type_vga:
		for (int i = 0; i < vec_position_vga_.size(); i++)
		{
			if (_forced || !vec_position_vga_[i]._used  && vec_position_vga_[i]._rt.containsPoint(_comp->getPosition()))
			{
				vec_position_vga_[i]._used = true;
				b_col = true;
				_comp->n_slot_idx_ = i;
				break;
			}

		}
		break;

	case component_type_storage:
		for (int i = 0; i < vec_position_storage_.size(); i++)
		{
			if (!vec_position_storage_[i]._used && (_forced || vec_position_storage_[i]._rt.containsPoint(_comp->getPosition())))
			{
				vec_position_storage_[i]._used = true;
				b_col = true;
				_comp->n_slot_idx_ = i;
				break;
			}

		}
		break;
	}


	if (b_col)
	{
		_comp->retain();
		_comp->removeFromParentAndCleanup(false);
		_comp->attached();
		if (_comp->getComponentType() == component_type_mainboard)
			addChild(_comp);
		else
		{
			_comp->setPosition(_comp->getPosition() - vec_component_[0]->getPosition() + vec_component_[0]->getContentSize() / 2);
			vec_component_[0]->addChild(_comp);

		}

		_comp->setZOrder(0);
		
		bool b_duplicate = false;
		for (CComponent* comp : vec_component_)
		{
			if (comp == _comp)
			{
				b_duplicate = true;
				break;
			}
		}
		
		if (!b_duplicate)
		{
			vec_component_.push_back(_comp);
			
		}

		//CGameManager::getInstance()->n_money_ -= _comp->getPrice();
		//CUILayer::getInstance()->updateMoney();

		vibe();
		if (!_forced)
			CSoundManager::getInstance()->playSfx("sound/attach.mp3");
			
		return true;
	}

	else
	{
		for (int i = 1; i < vec_component_.size(); i++)
		{
			if (vec_component_[i] == _comp)
			{
				vec_component_.erase(vec_component_.begin() + i);
				break;
			}
		}


	}



	return false;
}
int CDesk::getLeftPosition(CComponent* _comp)
{
	int left_over = 0;

	std::vector<Position> temp;
	switch (_comp->getComponentType())
	{
	case component_type_mainboard:
		temp = vec_position_main_board_;
		break;
	case component_type_cpu:
		temp = vec_position_cpu_;
		break;

	case component_type_ram:
		temp = vec_position_ram_;
		break;

	case component_type_power:
		temp = vec_position_power_;
		break;
	case component_type_vga:
		temp = vec_position_vga_;
		break;
	case component_type_storage:
		temp = vec_position_storage_;
		break;
		
	default:
		break;
	}

	for (auto com : temp)
	{
		if (!com._used)
			left_over++;
	}
	return left_over;
}
int CDesk::getUsedPosition(eCOMPONENTTYPE _type)
{
	int used = 0;

	std::vector<Position> temp;
	switch (_type)
	{
	case component_type_mainboard:
		temp = vec_position_main_board_;
		break;
	case component_type_cpu:
		temp = vec_position_cpu_;
		break;

	case component_type_ram:
		temp = vec_position_ram_;
		break;

	case component_type_power:
		temp = vec_position_power_;
		break;
	case component_type_vga:
		temp = vec_position_vga_;
		break;
	case component_type_storage:
		temp = vec_position_storage_;
		break;

	default:
		break;
	}

	for (auto com : temp)
	{
		if (com._used)
			used++;
	}
	return used;
}
void CDesk::checkDeleteComp(Vec2 _pos)
{

	for (int i = vec_component_.size() - 1; i >= 0; i--)
		
	{
		CComponent* comp = vec_component_[i];
		bool col = false;

		if (i == 0)
			col = comp->getBoundingBox().containsPoint(_pos);
		else
			col = comp->getBoundingBox().containsPoint(vec_component_[0]->convertToNodeSpace(_pos)); 
		if (col)
		{
			
			//vec_component_.erase(vec_component_.begin() + i);
			p_cur_delete_comp_ = comp;

			if (p_cur_delete_comp_->getComponentType() != component_type_mainboard)
			p_cur_delete_comp_->setPosition(p_cur_delete_comp_->getPosition() + vec_component_[0]->getPosition() - vec_component_[0]->getContentSize() / 2);
			//p_cur_delete_comp_->setPosition(_pos);


			p_cur_delete_comp_->retain();
			p_cur_delete_comp_->removeFromParent();
			
			p_cur_delete_comp_->detached();
			addChild(p_cur_delete_comp_);
			p_cur_delete_comp_->setZOrder(11);

			//CGameManager::getInstance()->n_money_ += p_cur_delete_comp_->getPrice();
			//CUILayer::getInstance()->updateMoney();
			switch (p_cur_delete_comp_->getComponentType())
			{
			case 	component_type_mainboard:
				vec_position_main_board_[p_cur_delete_comp_->n_slot_idx_]._used = false;
				e_make_step_ = e_step_one;
				break;
			case component_type_cpu:
				vec_position_cpu_[p_cur_delete_comp_->n_slot_idx_]._used = false;
				break;
			case component_type_ram:
				vec_position_ram_[p_cur_delete_comp_->n_slot_idx_]._used = false;
				break;
			case component_type_vga:
				vec_position_vga_[p_cur_delete_comp_->n_slot_idx_]._used = false;
				break;
			case component_type_storage:
				vec_position_storage_[p_cur_delete_comp_->n_slot_idx_]._used = false;
				break;
			case component_type_power:
				vec_position_power_[p_cur_delete_comp_->n_slot_idx_]._used = false;
				break;
			}
			ready(p_cur_delete_comp_);

			break;
		}

	}
}
bool CDesk::checkIsEnd()
{
	if (getUsedPosition(component_type_cpu) > 0 &&
		getUsedPosition(component_type_ram) > 0 &&
		getUsedPosition(component_type_power) > 0 &&
		getUsedPosition(component_type_storage) > 0 &&
		getUsedPosition(component_type_mainboard) > 0)
		return true;

	return false;
}

int CDesk::getScore(eCOMPONENTTYPE _type)
{
	int _score = 0;
	for (CComponent* comp : vec_component_)
	{
		if (comp->getComponentType() == _type)
			_score += comp->getValue();
	}

	return _score;
}
int CDesk::getTotalPrice()
{
	int _price = 0;
	for (CComponent* comp : vec_component_)
	{
		_price += comp->getPrice();
	}

	return _price;
}