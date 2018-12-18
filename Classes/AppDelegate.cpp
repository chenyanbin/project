#include "AppDelegate.h"
#include "commonData/GlobalInfo.h"
#include "module/login/LoginLayer.h"
#include "VisibleRect.h"
#include "sdk/SdkManager.h"
#include "YVSDK/YVPlatform.h"
#include "net/NetworkDataProcessing.h"
USING_NS_CC;
using namespace YVSDK;

//extern"C"{
//    
//    size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
//    
//    {
//        
//        return fwrite(a, b, c, d);
//        
//    }
//    
//    char* strerror$UNIX2003( int errnum )
//    
//    {
//        
//        return strerror(errnum);
//        
//    }
//
//    
//}
//=========================云娃SDK事件Dispatch类==================================
class DispatchMsgNode : public cocos2d::Node
{
public:
    bool init()
    {
        isschedule = false;
        return  Node::init();
    }
    CREATE_FUNC(DispatchMsgNode);
    void startDispatch()
    {
        if (isschedule) return;
        isschedule = true;
        
        Director::getInstance()->getScheduler()->schedule(schedule_selector(DispatchMsgNode::update), this, 0, false);
    }
    void stopDispatch()
    {
        if (!isschedule) return;
        isschedule = false;
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(DispatchMsgNode::update), this);
        
    }
    void update(float dt)
    {
       YVSDK::YVPlatform::getSingletonPtr()->updateSdk(dt);
    }
private:
    bool isschedule;
    
};
AppDelegate::AppDelegate():m_dispathMsgNode(NULL) {

}

AppDelegate::~AppDelegate() 
{
    CC_SAFE_RELEASE_NULL(m_dispathMsgNode);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
   
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("QiXiSanGuo");
        director->setOpenGLView(glview);
    }
  
    director->setContentScaleFactor(MIN(SDResource.size.height/designResolutionSize.height, SDResource.size.width/designResolutionSize.width));
    GlobalInfo::getInstance()->screenScaleX = VisibleRect::getVisibleRect().size.width/designResolutionSize.width;
    GlobalInfo::getInstance()->screenScaleY = VisibleRect::getVisibleRect().size.height/designResolutionSize.height;
//    log("VisibleRect::getVisibleRect().size.height===%f,scaleX=%f",VisibleRect::getVisibleRect().size.height,GlobalInfo::getInstance()->screenScaleX);
    // turn on display FPS
//    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
//    glClearColor(255, 255, 255, 1.0);
    // create a scene. it's an autorelease object

    
    Scene* scene = LoginLayer::createScene();
    // run
    director->runWithScene(scene);

    SdkManager::getInstance()->initSDK();
  

    if (m_dispathMsgNode == NULL)
    {
        YVPlatform* platform = YVPlatform::getSingletonPtr();
        platform->setConfig(ConfigAppid, YUNWA_APPID);
        platform->setConfig(ConfigTempPath, (FileUtils::getInstance()->getWritablePath()).c_str());
        platform->setConfig(ConfigIsTest, false);//true
        platform->setConfig(ConfigChannelKey, "0x001", NULL);
        platform->setConfig(ConfigServerId, "1");
        platform->setConfig(ConfigSpeechWhenSend, true);
       
        platform->init();
        m_dispathMsgNode = DispatchMsgNode::create();
        m_dispathMsgNode->retain();
        m_dispathMsgNode->startDispatch();
    }
   
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SoundManager::pauseBackgroundMusic();
   
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SoundManager::resumeBackgroundMusic();
    if(!NetworkDataProcessing::getInstance()->socketIsOk && GlobalInfo::getInstance()->gameRole->roleID != 0)
    {
        if(GlobalInfo::getInstance()->addressIP.size() <= 0 || GlobalInfo::getInstance()->port <= 0)
        {
            return;
        }
        NetworkDataProcessing::getInstance()->reConnectNet();
    }
    
}
