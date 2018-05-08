#include "GameManager.h"
#include "Assemble.h"
#include "Room.h"
#include "UILayer.h"
#include "Intro.h"
#include "Title.h"
#include "Clean.h"
#include "Ending.h"
#include "Reassemble.h"
#include "Quiz.h"

CGameManager::CGameManager()
{
	b_is_result_ = false;

	n_level_ = 1;
	n_count_ = 0;

	p_cur_layer_ = NULL;
}


CGameManager::~CGameManager()
{
}

CGameManager* CGameManager::getInstance()
{
	static CGameManager s_game_manager_;
	return &s_game_manager_;
}

bool CGameManager::init()
{
	p_layer_ = Layer::create();
	p_layer_->retain();

	srand(time(NULL));

	n_money_ = 500000;
	n_level_ = 1;

#ifdef IS_DEBUG
	n_level_ = 4;
	n_money_ = 100000000;
#endif
	initStage();
	if (n_level_ == 4)
		n_type_ = 0;
	else
		n_type_ = vec_stage_type_[n_count_];
#ifdef IS_DEBUG
	n_type_ = 0;
#endif
	return true;
}
void CGameManager::reGame()
{
	n_money_ = 500000;
	n_level_ = 1;
	n_count_ = 0;
	vec_stage_type_.clear();
	initStage();
	if (n_level_ == 4)
		n_type_ = 0;
	else
		n_type_ = vec_stage_type_[n_count_];

	n_cpu_score_ = 0;
	n_ram_score_ = 0;
	n_power_score_ = 0;
	n_storage_score_ = 0;
	n_vga_score_ = 0;
}
void CGameManager::initStage()
{
	
	if (n_level_ == 4)
		return;
	bool b_duplicate = false;
	for (int i = 0; i <4; i++)	//n_level_ * 4
	{
		b_duplicate = false;
		n_type_ = rand() % (n_level_ * 4);
		for (int j = 0; j < i + (n_level_-1) * 4; j++)
			if (vec_stage_type_[j] == n_type_)
			{
				i--;
				b_duplicate = true;
			}
		if (!b_duplicate)
			vec_stage_type_.push_back(n_type_);
	}
	
}
void CGameManager::changeState(eGAMESTATE _state, bool _fade)
{
	if (_fade)
	{

		auto p_fade_layer_ = LayerColor::create(Color4B::BLACK);
		p_fade_layer_->setOpacity(0);
		p_layer_->addChild(p_fade_layer_, 100);
		p_fade_layer_->setOpacity(0);

		p_fade_layer_->runAction(Sequence::create(FadeIn::create(0.8f), CallFunc::create([=](...){
			e_game_state_ = _state;
			if (p_cur_layer_)
				p_cur_layer_->removeFromParent();

			switch (e_game_state_)
			{
			case e_state_intro:
				p_cur_layer_ = CIntro::create();
				break;
			case e_state_title:
				p_cur_layer_ = CTitle::create();
				break;
			case e_state_room:
				p_cur_layer_ = CRoom::create();
			
				break;
			case e_state_assemble:
				p_cur_layer_ = CAssemble::create();
				break;

			case e_state_clean:
				p_cur_layer_ = CClean::create();
				break;
			case e_state_reassemble:
				p_cur_layer_ = CReassemble::create();
				break;
			case e_state_quiz:
				p_cur_layer_ = CQuiz::create();
				break;
			case e_state_ending:
				p_cur_layer_ = CEnding::create();
				break;
			default:
				break;
			}

			p_layer_->addChild(p_cur_layer_);
		}), FadeOut::create(0.8f), RemoveSelf::create(), NULL));

	}
	else
	{
		e_game_state_ = _state;
		if (p_cur_layer_)
			p_cur_layer_->removeFromParent();

		switch (e_game_state_)
		{
		case e_state_intro:
			p_cur_layer_ = CIntro::create();
			break;
		case e_state_title:
			p_cur_layer_ = CTitle::create();
			break;
		case e_state_room:
			p_cur_layer_ = CRoom::create();
			break;
		case e_state_assemble:
			p_cur_layer_ = CAssemble::create();
			break;
		case e_state_clean:
			p_cur_layer_ = CClean::create();
			break;
		case e_state_reassemble:
			p_cur_layer_ = CReassemble::create();
			break;
		case e_state_quiz:
			p_cur_layer_ = CQuiz::create();
			break;
		case e_state_ending:
			p_cur_layer_ = CEnding::create();
			break;
		default:
			break;
		}

		p_layer_->addChild(p_cur_layer_);
	}

	
}
Json::Value CGameManager::initJson(std::string _path)
{
	//Init Json
	std::string fileName = CCFileUtils::getInstance()->fullPathForFilename(_path);
	ssize_t bufferSize = 0;
	unsigned char* json = CCFileUtils::getInstance()->getFileData(fileName.c_str(), "rb", &bufferSize);

	std::string clearData((const char*)json);
	size_t pos = clearData.rfind("}");
	clearData = clearData.substr(0, pos + 1);

	Json::Value root;
	Json::Reader reader;

	if (reader.parse(clearData, root) == false)
	{
		log("JSON Parser fail");
		return NULL;
	}

	return root;
}
bool CGameManager::nextStage()
{
	

	n_count_++;
	n_count_ %= n_level_ * 4;
	

	if (n_money_ > n_level_ * 1000000 && n_level_ != 4)
	{
			n_level_++;
		//n_count_ = 0;

		//vec_stage_type_.clear();

		/*for (int i = 0; i < n_count_; i++)
		{
			vec_stage_type_.erase(vec_stage_type_.begin() + 0);
		}*/
		initStage();

		for (int i = 0; i < vec_stage_type_.size(); i++)
		{
			int temp, a, b;
			a = rand() % (vec_stage_type_.size() - n_count_) + n_count_;;
			b = rand() % (vec_stage_type_.size() - n_count_) + n_count_;

			temp = vec_stage_type_[a];
			vec_stage_type_[a] = vec_stage_type_[b];
			vec_stage_type_[b] = temp;
		}

		n_type_ = vec_stage_type_[n_count_];

		if (n_level_ == 4)
			n_count_ = 0;
	}

	if (n_level_ == 4)
	{
		n_type_ = n_count_;
		if (n_level_ == 4 && n_count_ == 4)
			return false;
		return true;
	}

	n_type_ = vec_stage_type_[n_count_];

	//if (n_level_ <= 3)
	


	return true;

	//return false;
}
