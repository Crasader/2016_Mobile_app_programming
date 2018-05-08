#pragma once
#include "cocos2d.h"
class CSoundManager
{
public:
	CSoundManager(void);
	~CSoundManager(void);

	static CSoundManager*				getInstance();

	void								playBGM(std::string _bgm_path, bool _loop = true);
	void								stopBGM();

	int									playSfx(std::string _sfx_path);
	void								preloadSfx(std::string _path);
	void								stopAllSfx();
	void								stopSfx(int _id);


	void								setBGMVolume(float _volume);
	void								setSfxVolume(float _volume); 

	bool								isPlayingBGM();

	void								pause();
	void								resume();

	void								FadeBGM(std::string _bgm_path, bool _fade = true);


private:
	int									n_bgm_id_;
	std::vector<int>					vec_effect_id_;
	

	float								f_bgm_volume_;
	float								f_sfx_volume_;
	float								f_fade_;
};

