#pragma once
#include <cocos2d.h>
#include "Component.h"
USING_NS_CC;

enum eMAKESTEP{
	e_step_one, // mainboard
	e_step_two, // other component in mainboard
	e_step_three, // case, hard...etc
	e_step_finish // do it all
};

struct Position
{
	Rect _rt;
	bool _used;
};

class CDesk : public Node
{
public:
	CDesk();
	~CDesk();
	
	CREATE_FUNC(CDesk);
	bool									init();
	void									positionInit();

	void									ready(CComponent* _comp);
	void									compMove(CComponent* _comp, Vec2 _pos, bool _forced = false);
	bool									attach(CComponent* _comp, bool _forced= false);
	int										getLeftPosition(CComponent* _comp);
	int										getUsedPosition(eCOMPONENTTYPE _type);

	void									checkDeleteComp(Vec2 _pos);
	void									touchBegan(Touch* touch);
	void									touchMove(Touch* touch);
	void									touchEnd(Touch* touch);

	bool									checkIsEnd();

	int										getScore(eCOMPONENTTYPE _type);
	int										getTotalPrice();

	eMAKESTEP							e_make_step_;

	std::vector<CComponent*>		vec_component_;


	std::vector<Position>				vec_position_main_board_;
	std::vector<Position>				vec_position_cpu_;
	std::vector<Position>				vec_position_ram_;
	std::vector<Position>				vec_position_storage_;
	std::vector<Position>				vec_position_vga_;
	std::vector<Position>				vec_position_power_;

	DrawNode*							p_draw_node_;

	CComponent*						p_cur_delete_comp_;
};

