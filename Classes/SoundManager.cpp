#include "SoundManager.h"
//#include "AudioEngine.h"
#include "SimpleAudioEngine.h"
#include "GameManager.h"
USING_NS_CC;

CSoundManager::CSoundManager(void)
{
	n_bgm_id_ = -1;
	vec_effect_id_.clear();

	f_bgm_volume_ = 1;
	f_sfx_volume_ = 1;
}


CSoundManager::~CSoundManager(void)
{
}
CSoundManager* CSoundManager::getInstance()
{
	static CSoundManager s_sound_manager_;
	return &s_sound_manager_;
}

void CSoundManager::playBGM(std::string _bgm_path, bool _loop)
{
	stopBGM();
	//n_bgm_id_ = experimental::AudioEngine::play2d (_bgm_path , true , f_bgm_volume_ );
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(_bgm_path.c_str(), _loop);
}
void CSoundManager::stopBGM()
{
	//if(n_bgm_id_ != -1)
	//{
		//experimental::AudioEngine::stop( n_bgm_id_ );
		//n_bgm_id_ = -1;
	//}
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
int CSoundManager::playSfx(std::string _sfx_path)
{
	//int n_id = experimental::AudioEngine::play2d( _sfx_path , false, f_sfx_volume_ );
	//vec_effect_id_.push_back( n_id );

	int n_id = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(_sfx_path.c_str(), false);
	return n_id;
}
void CSoundManager::stopAllSfx()
{
	/*for(int effect : vec_effect_id_)
	{
		experimental::AudioEngine::stop(effect);
	}

	vec_effect_id_.clear();*/
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
}
void CSoundManager::preloadSfx(std::string _path)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(_path.c_str());
}
void CSoundManager::setBGMVolume(float _volume)
{
	f_bgm_volume_ = _volume;

	/*if(n_bgm_id_ != -1)
		experimental::AudioEngine::setVolume(n_bgm_id_, f_bgm_volume_);*/

	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(f_bgm_volume_);
}
void CSoundManager::setSfxVolume(float _volume)
{
	f_sfx_volume_ = _volume;

	/*for(int _id : vec_effect_id_)
	{
		experimental::AudioEngine::setVolume(_id, f_sfx_volume_);
	}*/
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(_volume);
}
void CSoundManager::pause()
{
	//experimental::AudioEngine::pauseAll();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void CSoundManager::resume()
{
	//experimental::AudioEngine::resumeAll();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
bool CSoundManager::isPlayingBGM()
{
	//if (experimental::AudioEngine::getState(n_bgm_id_) == experimental::AudioEngine::AudioState::PLAYING)
	//	return true;

	CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	return false;
}
void CSoundManager::stopSfx(int _id)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(_id);
}
void CSoundManager::FadeBGM(std::string _bgm_path, bool _fade)
{
	
//	log("bgm : %.2f", CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() );
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	//if(isPlayingBGM())
//	{
//		f_fade_ = -0.08f;
//		CGameManager::getInstance()->getLayer()->schedule([=](...){
//			log("bgm : %.2f", CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() );
//			if (f_fade_ < 0.00000f)
//			{
//				CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() + f_fade_);
//				log("fade out..");
//				
//				if (CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() <= 0.1f)
//				{
//					playBGM(_bgm_path, _fade);
//					setBGMVolume(0.0f);
//					f_fade_ = 0.05f;
//					log("fade out end");
//					log("_bgm_path : %s", _bgm_path.c_str());
//				}
//			}
//			else
//			{
//				CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() + f_fade_);
//				log("fade in..");
//				if (CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() >= 0.5f)
//				{
//					log("fade in end");
//					CGameManager::getInstance()->getLayer()->unschedule("bgm_fade");
//				}
//			}
//
//		}, "bgm_fade");
//	}
//	/*else
//	{
//		playBGM(_bgm_path);
//		setBGMVolume(1.0f);
//	}*/
//	
//#else
//	playBGM(_bgm_path);
//	setBGMVolume(0.5f);
//#endif
	playBGM(_bgm_path);
}