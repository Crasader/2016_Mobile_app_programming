#pragma once
#include <cocos2d.h>
#include "json/json.h"
#include <math.h>
#define IS_DEBUG 1

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include <platform/android/jni/JniHelper.h>
#endif

USING_NS_CC;

enum eGAMESTATE{
	e_state_intro,
	e_state_title,
	e_state_room,
	e_state_assemble,
	e_state_clean,
	e_state_reassemble,
	e_state_quiz,
	e_state_ending
};


class CGameManager
{
public:
	CGameManager();
	~CGameManager();

	bool										init();

	static CGameManager*					getInstance();
	static Json::Value						initJson(std::string _path);
	Layer*										getLayer(){ return p_layer_; }

	bool										nextStage();
	void										initStage();

	void										reGame();
	void										changeState(eGAMESTATE _state, bool _fade = true);
	Layer*										p_layer_;
	Layer*										p_cur_layer_;


	eGAMESTATE							e_game_state_;

	bool										b_is_result_ = false;
	bool										b_is_success_ = false;

	int											n_level_;
	int											n_type_;				//스테이지,,
	int											n_count_;				//한 횟수.
	std::vector<int>							vec_stage_type_;		//중복피하기위해

	int											n_cpu_score_ = 0;		//npc가 요구하는 점수
	int											n_ram_score_ = 0;
	int											n_power_score_ = 0;
	int											n_storage_score_ = 0;
	int											n_vga_score_ = 0;


	int											n_money_;


};



inline const char* ANSIToUTF8(const char * pszCode)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	int		nLength, nLength2;
	BSTR	bstrCode;
	char*	pszUTFCode = NULL;

	nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), NULL, NULL);
	bstrCode = SysAllocStringLen(NULL, nLength);
	MultiByteToWideChar(CP_ACP, 0, pszCode, strlen(pszCode), bstrCode, nLength);

	nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL);
	pszUTFCode = (char*)malloc(nLength2 + 1);
	WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL);

	return pszUTFCode;
#else
	JniMethodInfo t;
	JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "changeStringToUTF8", "([B)Ljava/lang/String;");
	jbyteArray arr = (t.env)->NewByteArray(strlen(pszCode));
	(t.env)->SetByteArrayRegion(arr, 0, strlen(pszCode), (const jbyte*)pszCode);
	//jsize arrSize = t.env->GetArrayLength(arr);
	//jbyte *pbyte = (t.env)->GetByteArrayElements(arr, 0);
	jstring returnValue = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, arr);
	const char *nativeString = (t.env)->GetStringUTFChars(returnValue, 0);
	// Release
	//t.env->ReleaseByteArrayElements(arr, pbyte, 0);
	t.env->DeleteLocalRef(arr);
	t.env->DeleteLocalRef(t.classID);
	t.env->DeleteLocalRef(returnValue);
	//log("nativeString : %s", nativeString);
	return nativeString;
	//return pszCode;//JNICommunicator::changeStringToUTF8(pszCode);
#endif
}


inline int util_add_comma_to_num(const char *str, char *buf, int buflen)
{
	int len;
	int shift;

	/* count given string */
	len = strlen(str);
	shift = -len;

	assert(buflen >= (len + len / 3 + 1));

	while (*str)
	{
		*buf++ = *str++;
		if (++shift && (shift % 3) == 0)
			*buf++ = ',';
	}

	*buf = '\0';

	return 0;
}

inline double DegreeToRadian(double deg) {
	return deg * (3.1415f / 180);
}
inline double RadianToDegree(double rad) {
	return rad * (180 / 3.141592f);
}
inline double GetAngle(Vec2 p1, Vec2 p2) {
	double xdf = p2.x - p1.x;
	double ydf = p2.y - p1.y;
	
	//double ang = RadianToDegree(atan2(ydf, xdf));
	//return ang + 90;
	return atan2(ydf, xdf);
}


inline void vibe()
{	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "vibe", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

#endif
}
inline void startCleanSetting()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "startCleanSetting", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

#endif
}
inline void endCleanSetting()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "endCleanSetting", "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

#endif
}
inline float getDeviceXRotation()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	jfloat returnValue = 0;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "getDeviceXRotation", "()F"))
	{
		returnValue = (jfloat)t.env->CallStaticFloatMethod(t.classID, t.methodID);
		// Release
		t.env->DeleteLocalRef(t.classID);
	}
	return returnValue;
#endif

	return 0;
}

inline float getDeviceYRotation()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	jfloat returnValue = 0;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "getDeviceYRotation", "()F"))
	{
		returnValue = (jfloat)t.env->CallStaticFloatMethod(t.classID, t.methodID);
		// Release
		t.env->DeleteLocalRef(t.classID);
	}
	return returnValue;
#endif

	return 0;
}

inline float getMicLevel()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	jfloat returnValue = 0;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "getMicLevel", "()F"))
	{
		returnValue = (jfloat)t.env->CallStaticFloatMethod(t.classID, t.methodID);
		// Release
		t.env->DeleteLocalRef(t.classID);
	}
	return returnValue;
#endif

	return 0;
}

inline float getDeviceAccel()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	jfloat returnValue = 0;
	if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.ComputerMaker/AppActivity", "getDeviceAccel", "()F"))
	{
		returnValue = (jfloat)t.env->CallStaticFloatMethod(t.classID, t.methodID);
		// Release
		t.env->DeleteLocalRef(t.classID);
	}
	return returnValue;
#endif

	return 0;
}