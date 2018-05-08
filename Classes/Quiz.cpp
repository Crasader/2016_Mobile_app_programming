#include "Quiz.h"
#include "GameManager.h"
#include "UILayer.h"
#include "SoundManager.h"

CQuiz::CQuiz()
{
	n_count_ = 1;
	p_chat_ = NULL;
}


CQuiz::~CQuiz()
{
}

bool CQuiz::init()
{
	CUILayer::getInstance()->setVisible(false);
	//CGameManager::getInstance()->n_level_ = 4;
	//CGameManager::getInstance()->n_type_ = 2;
	/* bg init */
	auto p_bg = Sprite::create("room/bg_" + StringUtils::toString(CGameManager::getInstance()->n_level_) + ".png");
	p_bg->setPosition(Director::getInstance()->getWinSize() / 2);
	addChild(p_bg);
	
	//board
	auto board = Sprite::create("board.png");
	board->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	board->setPosition(0, 720);
	addChild(board);

	p_guest_ = CGuest::create();
	p_guest_->initWithData(CGameManager::getInstance()->n_level_, CGameManager::getInstance()->n_type_);
	addChild(p_guest_);
	
	j_val_ = CGameManager::getInstance()->initJson("room/guest/guest_info_" + StringUtils::toString(CGameManager::getInstance()->n_level_ )+ ".json");

	//정답초기화
	for (int i = 0; i < j_val_["info"][CGameManager::getInstance()->n_type_]["quiz_answer"].size(); i++)
		vec_answer_.push_back(j_val_["info"][CGameManager::getInstance()->n_type_]["quiz_answer"][i].asInt());


	
	p_menu_ = Menu::create();
	p_menu_->setPosition(0, 0);
	addChild(p_menu_);
	initStage();
	 

	return true;
}

void CQuiz::initStage()
{
	if (p_chat_)
		p_chat_->removeFromParent();

	for (MenuItemFont* _font : vec_menu_)
		_font->runAction(Sequence::create(DelayTime::create(0), RemoveSelf::create(), NULL));
	vec_menu_.clear();



	std::vector<std::string> vec_question;
	for (int i = 0; i < j_val_["info"][CGameManager::getInstance()->n_type_]["quiz_question_" + StringUtils::toString(n_count_)].size(); i++)
		vec_question.push_back(j_val_["info"][CGameManager::getInstance()->n_type_]["quiz_question_" + StringUtils::toString(n_count_)][i].asString());

	std::vector<std::string> vec_text;
	for (int i = 0; i < j_val_["info"][CGameManager::getInstance()->n_type_]["quiz_text_" + StringUtils::toString(n_count_)].size(); i++)
		vec_text.push_back(j_val_["info"][CGameManager::getInstance()->n_type_]["quiz_text_" + StringUtils::toString(n_count_)][i].asString());


	p_chat_ = CChat::create();
	p_chat_->initChat(p_guest_->str_name_, vec_text);
	addChild(p_chat_);

	//퀴즈 문제 생성
	for (int i = 0; i < vec_question.size(); i++)
	{
		MenuItemFont* p_item = MenuItemFont::create(vec_question[i], [=](Ref* ref){
		
			int result = dynamic_cast<MenuItemFont*>(ref)->getTag();

			if (result)
			{
				for (MenuItemFont* _font : vec_menu_)
					_font->setEnabled(false);
				
				CSoundManager::getInstance()->playSfx("sound/correct.mp3");

				auto correct = Sprite::create("correct.png");
				correct->setPosition(29, dynamic_cast<MenuItemFont*>(ref)->getPosition().y);
				addChild(correct);

				scheduleOnce([=](...){
					correct->removeFromParent();
					n_count_++;

					if (n_count_ > 3)
					{
						CGameManager::getInstance()->b_is_result_ = true;
						CGameManager::getInstance()->b_is_success_ = true;
						CGameManager::getInstance()->changeState(e_state_room);
					}
					else
						initStage();

				}, 1.0f, "next");
			}
			else
			{
				CSoundManager::getInstance()->playSfx("sound/wrong.mp3");
			}
		
		});
		p_item->setFontNameObj("BM-HANNA.ttf");
		p_item->setFontSizeObj(50);
		p_item->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		p_item->setPosition(50, 650 - 115 * i);
		dynamic_cast<Label*>(p_item->getLabel())->enableOutline(Color4B::BLACK, 5);
		if (i == vec_answer_[n_count_ - 1])
			p_item->setTag(true);
		else
			p_item->setTag(false);

		vec_menu_.push_back(p_item);

		p_menu_->addChild(p_item);
	}

}