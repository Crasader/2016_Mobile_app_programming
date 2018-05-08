#include "Title.h"
#include "SoundManager.h"
#include "GameManager.h"
CTitle::CTitle()
{
}


CTitle::~CTitle()
{
}

bool CTitle::init()
{

	auto bg = Sprite::create("title/bg.png");
	bg->setPosition(Director::getInstance()->getWinSize() / 2);
	addChild(bg);

	auto title = Sprite::create("title/title.png");
	title->setPosition(640, 370);
	title->setScale(0.8f);
	title->setOpacity(0);
	title->runAction(Sequence::create(DelayTime::create(0.7f), Spawn::create((MoveBy::create(0.7f, Vec2(0, 50))), FadeIn::create(0.7f), NULL), NULL));
	addChild(title, 1);

	

	Menu* p_menu = Menu::create();
	p_menu->setPosition(0, 0);
	addChild(p_menu);

	MenuItemImage* p_item = MenuItemImage::create("title/button_1.png", "title/button_2.png", [=](...){
		CGameManager::getInstance()->changeState(e_state_room);
	});
	p_item->runAction(Sequence::create(DelayTime::create(0.7f), FadeIn::create(0.7f), NULL));
	p_item->setPosition(640, 150);
	p_item->setScale(0.7f);
	p_item->setOpacity(0);
	p_menu->addChild(p_item);


	CSoundManager::getInstance()->playBGM("sound/title_bgm.mp3");
	
	ParticleSystemQuad* p_part;
	p_part = ParticleSystemQuad::create("title/particle_texture.plist");
	p_part->setPosition(100, 800);
	p_part->setContentSize(Size(1000, 10));
	addChild(p_part);


	return true;
}