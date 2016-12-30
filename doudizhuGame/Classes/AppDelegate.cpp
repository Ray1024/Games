#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {

		glview = GLViewImpl::create("doudizhuGame");
		director->setOpenGLView(glview);
	}

	// 根据不同平台设置不同分辨率，设计尺寸设置为一样的
	Size designSize = Size(960, 540);
	Size frameSize;
	auto platform = this->getTargetPlatform();
	if (Application::Platform::OS_ANDROID == platform)
	{
		frameSize = Size(1920, 1080);
	} else if (Application::Platform::OS_WINDOWS == platform)
	{
		frameSize = Size(960, 540);
	}
	glview->setFrameSize(frameSize.width, frameSize.height);
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
	
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = GameScene::scene();

    // run
    director->runWithScene(scene);
	
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
