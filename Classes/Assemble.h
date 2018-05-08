#pragma once
#include <cocos2d.h>
#include "Desk.h"
#include "AssembleMenu.h"
#include "Component.h"
#include "Explain.h"
USING_NS_CC;

class CAssemble : public Layer
{
public:
	
	CAssemble();
	~CAssemble();

	CREATE_FUNC(CAssemble);
	bool init();
	void initTouch();
	bool onTouchBegan(Touch* touch, Event* unused_event); 
	void onTouchMoved(Touch* touch, Event* _event);
	void onTouchEnded(Touch* touch, Event* _event);

	void checkIsEnd();
private:
	CDesk*									p_desk_;
	CAssembleMenu*						p_assemble_menu_;

	CComponent*							p_cur_component_;

	MenuItemImage*						p_complete_;
	CExplain*									p_explain_;
	Label*										p_price_label_;
};

