#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SoundManager.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}
void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("My Game");

		glview->setFrameSize(1280, 720);
		//glview->setFrameZoomFactor(0.8);
		director->setOpenGLView(glview);
	}
	glview->setDesignResolutionSize(1280, 720, kResolutionExactFit);
    director->setDisplayStats(false);

    director->setAnimationInterval(1.0 / 60);

    auto scene = HelloWorld::createScene();

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CSoundManager::getInstance()->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CSoundManager::getInstance()->resume();
}
