#pragma once
#include <cocos2d.h>

USING_NS_CC;

enum eCOMPONENTTYPE{
	component_type_mainboard,
	component_type_cpu,
	component_type_ram,
	component_type_vga,
	component_type_storage,
	component_type_power
};

class CComponent : public Sprite
{
public:
	CComponent();
	~CComponent();

	CREATE_FUNC(CComponent);
	bool init();
	bool initWithType(eCOMPONENTTYPE _type, int _value , std::string _file_name, int price);
	eCOMPONENTTYPE						getComponentType(){ return e_component_type_; }
	std::string									getTypeToName();
	int											getValue(){	return n_value_;	}
	int											getPrice(){ return n_price_; }

	void										attached();
	void										detached();

	int											n_slot_idx_;
	int											n_idx_;
private:
	eCOMPONENTTYPE						e_component_type_;
	int											n_value_;
	int											n_price_;
	std::string									str_file_name_;

};


class CComponentFactory
{
public :
	static CComponent* createComponent(std::string _name, int value, int idx);
	static eCOMPONENTTYPE nameToType(std::string _name);
	
};
