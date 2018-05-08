#include "Component.h"
#include "GameManager.h"

CComponent::CComponent()
{
	n_slot_idx_ = -1;
}


CComponent::~CComponent()
{
}

bool CComponent::init()
{
	Sprite::init();
	return true;
}

bool CComponent::initWithType(eCOMPONENTTYPE _type, int _value, std::string _file_name, int price)
{
	e_component_type_ = _type;
	n_value_ = _value;
	str_file_name_ = _file_name;
	n_price_ = price;
	initWithFile(_file_name);

	return true;
}

std::string CComponent::getTypeToName()
{
	switch (e_component_type_)
	{
	case component_type_mainboard:
		return "main_board";
		break;
	case component_type_cpu:
		return "cpu";
		break;
	case component_type_ram:
		return "ram";
		break;
	case component_type_vga:
		return "vga";
		break;
	case component_type_storage:
		return "storage";
		break;
	case component_type_power:
		return "power";
		break;
	default:
		break;
	}
}
void CComponent::attached()
{
	if (e_component_type_ == component_type_ram)
	{
		setTexture("assemble/component/ram_attached.png");
		setPositionY(getPositionY() + 12);
	}
}
void CComponent::detached()
{
	if (e_component_type_ == component_type_ram)
		setTexture(str_file_name_);
}














CComponent*  CComponentFactory::createComponent(std::string _name, int value, int idx)
{
	CComponent* component = CComponent::create();
	Json::Value json_left_menu = CGameManager::initJson("assemble/left_menu/" + _name + "_info.json");
	

	component->initWithType(CComponentFactory::nameToType(_name), value, "assemble/component/" + _name + "_" + StringUtils::toString(idx) + ".png", json_left_menu["info"][idx-1]["price"].asInt());
	component->n_idx_ = idx;
	return component;
}

eCOMPONENTTYPE CComponentFactory::nameToType(std::string _name)
{
	if (_name == "main_board")
		return component_type_mainboard;
	else if (_name == "cpu")
		return component_type_cpu;
	else if (_name == "ram")
		return component_type_ram;
	else if (_name == "vga")
		return component_type_vga;
	else if (_name == "power")
		return component_type_power;
	else if (_name == "storage")
		return component_type_storage;

}