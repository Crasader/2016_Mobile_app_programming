//  cocos2d-x 3.x �������� ��� ���� �մϴ�.

//  ScrollMenu.h
//  Solitaire
//
//  Created by Kyung-Min Park on 2015. 4. 6..

#pragma once

#include <stdio.h>
#include <cocos2d.h>

using namespace cocos2d;

class ScrollMenu :public Menu
{
public:
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);

	static ScrollMenu* createWithArray(const Vector<MenuItem*>& arrayOfItems);
	static ScrollMenu* createWithItem(MenuItem* item);
	static ScrollMenu* createWithItems(MenuItem *firstItem, va_list args);
	static ScrollMenu* create(MenuItem* item, ...);

	bool init();
	bool initWithArray(const Vector<MenuItem*>& arrayOfItems);

private:
	bool isTouching;

	Vec2 m_touchesStart;
	Vec2 m_touchesEnd;
};