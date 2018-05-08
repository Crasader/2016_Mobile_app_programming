#pragma once
#include <cocos2d.h>
#include "Guest.h"
#include "Chat.h"

USING_NS_CC;

class CRoom : public Layer
{
public:
	CRoom();
	~CRoom();

	CREATE_FUNC(CRoom);

	bool											init();

	void											waitGuest();
	void											showResult();
	void											ending();
	void											initTouch();

	
	CGuest*										p_guest_;

	CChat*										p_chat_;
	Sprite*										p_bg_;

};

