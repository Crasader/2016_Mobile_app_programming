#pragma once
#include <cocos2d.h>
USING_NS_CC;

class CScrollViewLayer : public Layer
{
public:
	CScrollViewLayer();
	~CScrollViewLayer();
	CREATE_FUNC(CScrollViewLayer);
	bool												init();

	bool												onTouchBegan(Touch* touch, Event* unused_event);
	void												onTouchMoved(Touch* touch, Event* unused_event);
	void												onTouchEnded(Touch* touch, Event* unused_event);


	void												updateScroll();
	void												scroll(float dt);

	void												addObject(Node* _node);
	std::vector<Node*>								getObjectVector(){ return vec_index_object_; }


	bool												b_is_index_scroll_;
	float												f_index_scroll_dt_;
	float												f_index_scroll_speed_;
	float												f_min_index_scroll_num_;
	float												f_max_index_scroll_num_;

	void												clear();


	std::vector<Node*>								vec_index_object_;

	EventListenerTouchOneByOne*							p_listener_;

	Vec2												pt_touch_pos;

};

