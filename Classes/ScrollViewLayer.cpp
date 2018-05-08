#include "ScrollViewLayer.h"

#define SCROLL_FACTOR 0.9

CScrollViewLayer::CScrollViewLayer()
{
}


CScrollViewLayer::~CScrollViewLayer()
{
}

bool CScrollViewLayer::init()
{

	////ÅÍÄ¡
	//p_listener_ = EventListenerTouchOneByOne::create();
	//p_listener_->setSwallowTouches(true);
	//p_listener_->onTouchBegan = CC_CALLBACK_2(CScrollViewLayer::onTouchBegan, this);
	//p_listener_->onTouchMoved = CC_CALLBACK_2(CScrollViewLayer::onTouchMoved, this);
	//p_listener_->onTouchEnded = CC_CALLBACK_2(CScrollViewLayer::onTouchEnded, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(p_listener_, this);

	schedule(schedule_selector(CScrollViewLayer::scroll));

	b_is_index_scroll_ = false;
	f_index_scroll_dt_ = 0;
	f_index_scroll_speed_ = 0;

	f_min_index_scroll_num_ = -0;
	f_max_index_scroll_num_ = 0;
	if (vec_index_object_.size() > 0){
		f_max_index_scroll_num_ = vec_index_object_[0]->getContentSize().height * vec_index_object_.size() - (Director::getInstance()->getWinSize().height - getContentSize().height - getContentSize().height) + 0;
		if (f_max_index_scroll_num_ < 0)
			f_max_index_scroll_num_ = f_min_index_scroll_num_;
	}


	return true;
}
void CScrollViewLayer::addObject(Node* _node)
{
	vec_index_object_.push_back(_node);
	addChild(_node);

	f_min_index_scroll_num_ = -0;
	f_max_index_scroll_num_ = 0;
	if (vec_index_object_.size() > 0){
		f_max_index_scroll_num_ = vec_index_object_[0]->getContentSize().height * vec_index_object_.size() - (Director::getInstance()->getWinSize().height ) + 0;
		if (f_max_index_scroll_num_ < 0)
			f_max_index_scroll_num_ = f_min_index_scroll_num_;
	}
}
void CScrollViewLayer::clear()
{
	removeAllChildren();
	vec_index_object_.clear();
}
bool CScrollViewLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 pos = touch->getLocation();
	pt_touch_pos = Vec2(-1, -1);
	if (!getBoundingBox().containsPoint(pos))
		return false;

	pt_touch_pos = pos;
	return true;
}
void CScrollViewLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
	Vec2 pos = touch->getLocation();
	if (getBoundingBox().containsPoint(pos))
	{
		if (vec_index_object_.size() < 1)
			return;

		f_index_scroll_dt_ += (touch->getLocation().y - touch->getPreviousLocation().y) /4;

		if (f_index_scroll_dt_ < f_min_index_scroll_num_)
			f_index_scroll_dt_ = f_min_index_scroll_num_;
		else if (f_index_scroll_dt_ > f_max_index_scroll_num_)
			f_index_scroll_dt_ = f_max_index_scroll_num_;

		updateScroll();

		f_index_scroll_speed_ = (touch->getLocation().y - touch->getPreviousLocation().y) ;
	}
}
void CScrollViewLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
	Vec2 pos = touch->getLocation();
	if (getBoundingBox().containsPoint(pos))
	{
		b_is_index_scroll_ = false;
	}

	//if (pt_touch_pos.distance(touch->getLocation()) > MAX_TOUCH_DISTANCE ||
	//	pt_touch_pos == Vec2(-1, -1))
	//	return;

	//for (int i = 0; i < vec_image_object_.size(); i++)
	//{
	//	if (vec_image_object_[i]->getBoundingBox().containsPoint(pt_touch_pos) && vec_image_object_[i]->getBoundingBox().containsPoint(touch->getLocation()))
	//	{
	//		openImage(i);
	//		return;
	//	}
	//}
	///* if touch's y position is touched bottom layer, return.*/
	//if (p_bottom_layer_->getBoundingBox().containsPoint(touch->getLocation()))// touch->getLocation().y < p_bottom_layer_->getPositionY() + p_bottom_layer_->getContentSize().height )
	//	return;

	//for (int i = 0; i < vec_index_object_.size(); i++)
	//{
	//	if (vec_index_object_[i]->getBoundingBox().containsPoint(pt_touch_pos) && vec_index_object_[i]->getBoundingBox().containsPoint(touch->getLocation()))
	//	{
	//		openIndex(i);
	//		return;
	//	}
	//}

}

void CScrollViewLayer::updateScroll()
{
	for (int i = 0; i < vec_index_object_.size(); i++)
	{
		vec_index_object_[i]->setPositionY(getContentSize().height - vec_index_object_[i]->getContentSize().height /2 - vec_index_object_[i]->getContentSize().height * i + f_index_scroll_dt_);
	}
}
void CScrollViewLayer::scroll(float dt)
{
	
	if (!b_is_index_scroll_)
	{
		f_index_scroll_speed_ *= SCROLL_FACTOR;
		f_index_scroll_dt_ += f_index_scroll_speed_;

		if (f_index_scroll_dt_ < f_min_index_scroll_num_)
			f_index_scroll_dt_ = f_min_index_scroll_num_;
		else if (f_index_scroll_dt_ > f_max_index_scroll_num_)
			f_index_scroll_dt_ = f_max_index_scroll_num_;

		updateScroll();
	}
	//else
	//	f_scroll_dt_ -= f_scroll_dt_ * SCROLL_FACTOR;




}
