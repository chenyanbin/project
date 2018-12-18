//
//  VideoPlayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/14.
//
//
#include "VideoPlayer.hpp"
#include "../../common/PublicShowUI.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ios/LHVideoPlayerImplCpp.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#include <android/log.h>
#endif


VideoPlayer::VideoPlayer()
:onPlayFinished(NULL)
{
    
}
VideoPlayer::~VideoPlayer()
{
    
}
bool VideoPlayer::init()
{
    return true;
}

void VideoPlayer::play(const char* path)
{
    std::string jpath = path;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    Size visibleSize = Director::getInstance()->getVisibleSize();
    LHVideoPlayerImplCpp::playMP4WithName(path, Rect(0, 0, visibleSize.width, visibleSize.height));
    LHVideoPlayerImplCpp::setSkipTitle("跳过");
#endif
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    jobject jobj;
    //getStaticMethodInfo方法是调用静态类的，也可以不用调用静态类的getMethodInfo
    bool b = JniHelper::getStaticMethodInfo(minfo,
                                            "org.cocos2dx.cpp.AppActivity", //类路径
                                            "playVideo", //静态方法名
                                            "(Ljava/lang/String;)V");
    if(!b){
        log("JniHelper::getMethodInfo error...");
    }else{
        jpath = "video/" + jpath + ".mp4";
        jstring filePath=minfo.env->NewStringUTF(jpath.c_str());
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,filePath);
        minfo.env->DeleteLocalRef(minfo.classID);
        minfo.env->DeleteLocalRef(filePath);
    }

    #endif
  
    Director::getInstance()->getScheduler()->scheduleUpdate(this, .3, false);
    
   
    
}
void VideoPlayer::onEnter()
{
    Node::onEnter();
//   setJumpBtn();
}
void VideoPlayer::onExit()
{
      Node::onExit();
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}
void VideoPlayer::update(float dt)
{
  
    bool isfinished = false;
    #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
        isfinished = LHVideoPlayerImplCpp::isPlayFinished();
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo minfo;
        jboolean jobj;
        
        //getStaticMethodInfo方法是调用静态类的，也可以不用调用静态类的getMethodInfo
        bool b = JniHelper::getStaticMethodInfo(minfo,
                                                "org.cocos2dx.cpp.AppActivity", //类路径
                                                "isPlayFinished", //静态方法名
                                                "()Z");
        if(!b)
        {
            log("JniHelper::getMethodInfo error...");
        }
        else
        {
            
            jobj = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
            isfinished = jobj;
            minfo.env->DeleteLocalRef(minfo.classID);
        }

    #endif
    if(isfinished )
    {
        log("视频播放完毕=%d",isfinished);
        Director::getInstance()->getScheduler()->unscheduleUpdate(this);
        
        if(onPlayFinished)
        {
            onPlayFinished(this);
        }
    }
}

void VideoPlayer::setJumpBtn()
{
    Label* label = PublicShowUI::getLabel("跳过",Color3B::WHITE,24,false,true);
    label->setAnchorPoint(Point::ZERO);
    MenuItemLabel* itemLabel = MenuItemLabel::create(label, CC_CALLBACK_1(VideoPlayer::onJumpClick, this));
    itemLabel->setAnchorPoint(Point::ZERO);
    Size size =Director::getInstance()->getWinSize();
    float sx = GlobalInfo::getInstance()->screenScaleX;
    itemLabel->setPosition(size.width - itemLabel->getContentSize().width - 10 * sx, 20 * sx);
    
    Menu* menu = Menu::createWithItem(itemLabel);
//    Director::getInstance()->ge// ->addChild(menu,10);
    Scene* scene = Director::getInstance()->getRunningScene();
    scene->addChild(menu ,90000);
}
void VideoPlayer::onJumpClick(Ref* pSender)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    LHVideoPlayerImplCpp::skipMovie();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;

    
    //getStaticMethodInfo方法是调用静态类的，也可以不用调用静态类的getMethodInfo
    bool b = JniHelper::getStaticMethodInfo(minfo,
                                            "org.cocos2dx.cpp.AppActivity", //类路径
                                            "skipvideo", //静态方法名
                                            "()V");
    if(!b)
    {
        log("JniHelper::getMethodInfo error...");
    }
    else
    {
        
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    
#endif
}
