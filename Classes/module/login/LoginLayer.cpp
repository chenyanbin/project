//
//  LoginLayer.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/6/8.
//
//

#include "LoginLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../homeUI/HomeScene.h"
#include "../../commonData/dictData/ConfigFileReader.h"
#include "../homeUI/HomeLoader.h"
#include "userLogin/UserLoginLayer.h"
#include "../../sdk/SdkManager.h"
#include "../../net/HttpURLManager.h"
#include "serverList/ServerListDataManager.h"
#include "../../message/Decoding/loginMsg/LoginMsg.h"
#include "../../message/Decoding/loginMsg/RoleInfoMsg.h"
#include "../../net/NetworkDataProcessing.h"
#include "../../common/noticeManager/NoticeManager.h"
#include "../storyTalk/StoryTalkManager.h"
#include "../../common/StringUtil.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "../../commonData/data/FunctionOpenManager.h"
#include "../newPlayerGuide/NewPlayerGuild.h"
#include "../battle/BattleLoader.h"
#include "../assetsLoading/AssetsDownLoad.h"
#include "../../commonData/enum/DictFunctionEnum.h"
#include "../logigBattle/LoginBattle.h"
#include "../../YVSDK/YVPlatform.h"
#include "../awardBox/AwardBox_Layer.h"
#include "../../tdTalkData/TDTalkDataManager.hpp"
#include "YayaLoginListen.hpp"
#include "../../common/videoPlayer/VideoPlayer.hpp"
#include "../battleTest/PlayerDataManager.hpp"

LoginLayer::LoginLayer()
:TAG_SDKBTN(1)
,TAG_VERSION(2)
,TAG_VIDEO(3)
{
    
}
LoginLayer::~LoginLayer()
{

}
bool LoginLayer::init()
{
    bool bref = false;
    do {
  
        CC_BREAK_IF(!BaseLayer::init());
        this->isAnimation = false;
        this->isShowGrayBg = false;
        this->isAbleGuiding = false;
        GlobalInfo::getInstance()->addressIP = "";
        GlobalInfo::getInstance()->port = 0;
        if(!GlobalInfo::getInstance()->isEnterLogin)
        {
            initInfoPlist();
        }

        bref = true;
    } while (false);
    return bref;
}
Scene* LoginLayer::createScene(int fromeScene)
{
    Scene* scene = Scene::create();
    LoginLayer* layer = LoginLayer::create();
    layer->setFromScene(fromeScene);
    scene->addChild(layer, 0, SCENE_TAG_LOADING);
    return scene;
}
void LoginLayer::setVideo()
{
    Dialog::hideServerLoading();
    SoundManager::pauseBackgroundMusic();
    if(!ArmatureDataManager::getInstance()->getAnimationData("dengluliemian"))
    {
        ArmatureDataManager::getInstance()->removeArmatureFileInfo(IMG_LOGIN_BG_EFFECT);
        ArmatureDataManager::getInstance()->addArmatureFileInfo(IMG_LOGIN_BG_EFFECT);
    }
    VideoPlayer* video = VideoPlayer::create();
    video->play(BEGAIN_VIDEO);
    this->addChild(video,2,TAG_VIDEO);
    video->onPlayFinished = CC_CALLBACK_1(LoginLayer::onVideFinished, this);
}
void LoginLayer::onVideFinished(Ref* target)
{
//    PlayerDataManager::getInstance()->initData();
//    return;
    Dialog::showServerLoading(0);
    SdkManager::getInstance()->startLogin();
    this->removeChildByTag(TAG_VIDEO);
    setBackground();
}
void LoginLayer::setBackground()
{
    
    SoundManager::resumeBackgroundMusic();
    Armature* armature = Armature::create("dengluliemian");
    armature->getAnimation()->playWithIndex(0);
  
    float last_X = ( (float)VisibleRect::getVisibleRect().size.width/ SDResource.size.width) ;
    float last_Y = ( (float)VisibleRect::getVisibleRect().size.height/SDResource.size.height);
    float sx = last_X > last_Y ? last_X : last_Y;

  
    armature->setPosition(VisibleRect::center());
    armature->setScale(sx);
    this->addChild(armature, 0, TAG_BG);
}
void LoginLayer::setLoginSdkBtn()
{
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(LAYER_ENTER_GAME))
    {
        scene->removeChildByTag(LAYER_ENTER_GAME);
    }
    Button* btn = Button::create(IMG_LOADING_LOGINBTN, IMG_LOADING_LOGINBTN, CC_CALLBACK_1(LoginLayer::onLoginClick, this));
    btn->setAnchorPoint(Point::ZERO);
    PublicShowUI::setTargetScale(btn);
    btn->setPosition((this->getContentSize().width - btn->getContentSize().width)/2, 70 * GlobalInfo::getInstance()->screenScaleX);
    this->addChild(btn,3,TAG_SDKBTN);
}
void LoginLayer::onLoginClick(Ref* pSender)
{
    if(this->getChildByTag(TAG_SDKBTN))
    {
        this->removeChildByTag(TAG_SDKBTN);
    }
    
    SdkManager::getInstance()->startLogin();

}
void LoginLayer::requestEnterGameMsg()
{
    LoginMsg* msg = new LoginMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
void LoginLayer::enterMainUI()
{
    

    UserDefault::getInstance()->setBoolForKey("QIXI_ISLOADED", true);
    UserDefault::getInstance()->flush();
    GlobalInfo::getInstance()->isPlayedGuideBattle = false;
    Dialog::showServerLoading(.5);
    RoleInfoMsg* msg = new RoleInfoMsg();
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
   
}

void LoginLayer::loadConfigFile(EventCustom* event)
{
    ConfigFileReader::getInstance()->loadConfig();
    ConfigFileReader::destroyInstance();
    
    StoryTalkManager::getInstance();
}
void LoginLayer::onEnter()
{
    GlobalInfo::getInstance()->gameRole->roleID = 0;
    BaseLayer::onEnter();
    if(!GlobalInfo::getInstance()->isEnterLogin)
    {
        YayaLoginListen::getInstance()->initListener();
    }
    
     SoundManager::playBackgroundMusic(MUSIC_LOGIN);
    this->setClickEnabled(true);
}
void LoginLayer::onExit()
{
    BaseLayer::onExit();
    this->setClickEnabled(false);
}
void LoginLayer::onExitTransitionDidStart()
{
    BaseLayer::onExitTransitionDidStart();
    ServerListDataManager::getInstance()->destoryInstance();
}
void LoginLayer::onEnterTransitionDidFinish()
{
    BaseLayer::onEnterTransitionDidFinish();
    
  
    if(GlobalInfo::getInstance()->isEnterLogin)
    {
        onClientAppSuc(NULL);
    }
    else
    {
        addAssetsLoading();
    }
    updateVersion();
    
}
void LoginLayer::addAssetsLoading()
{
    AssetsDownLoad* loading = AssetsDownLoad::create();
    Director::getInstance()->getRunningScene()->addChild(loading,SCENE_POPLAYER_ZORDER);
}
//void LoginLayer::onCPLoginListern(YVSDK::CPLoginResponce* r)
//{
//    
//    log("nickname===%s",r->nickName.c_str());
//    if (r->result != 0 && GlobalInfo::getInstance()->isDebug)
//    {
//        Dialog::show(r->msg.c_str());
//        return;
//    }
//    GlobalInfo::getInstance()->gameRole->yayaId=r->userid;
////    enterMainUI();
// 
//}
//
//void LoginLayer::onYYLoginListern(YVSDK::LoginResponse* r)
//{
//    if (r->result != 0)
//    {
//        //MsgPopup::getSingletonPtr()->show(this->getScene());
//         Dialog::show(r->msg.c_str());
//        return;
//    }
//    schedule(schedule_selector(LoginLayer::delaytime), 1);
//}
void LoginLayer::delaytime(float dt)
{
    unschedule(schedule_selector(LoginLayer::delaytime));

//    YVSDK::YVPlatform::getSingletonPtr()->delYYLoginListern(this);
     enterMainUI();
}
//void LoginLayer::onGetCpuUserListern(YVSDK::GetCpmsgRepond* r)
//{
//   log("%s",r->nickname.c_str());
//}

void LoginLayer::initInfoPlist()
{
    const char *path="infoConfig.plist";
    Configuration::getInstance()->loadConfigFile(path);
    GlobalInfo::getInstance()->isAutoDownClient = Configuration::getInstance()->getValue("isAutoDownClient").asBool();
    GlobalInfo::getInstance()->isSdkMode = Configuration::getInstance()->getValue("isSdkMode").asBool();
//    GlobalInfo::getInstance()->loginPort = ":" + Configuration::getInstance()->getValue("loginPort").asString();
    GlobalInfo::getInstance()->isNativeMode = Configuration::getInstance()->getValue("isNative").asBool();
    GlobalInfo::getInstance()->isShowGuide = Configuration::getInstance()->getValue("isShowNewPlayerGuide").asBool();;
    GlobalInfo::getInstance()->isDebug = Configuration::getInstance()->getValue("isDebug").asBool();
    GlobalInfo::getInstance()->subChannelActive = Configuration::getInstance()->getValue("subChannelActive").asString();
    GlobalInfo::getInstance()->subChannel = Configuration::getInstance()->getValue("subChannel").asString();
    GlobalInfo::getInstance()->serverListURL = Configuration::getInstance()->getValue("serverListURL").asString();
    GlobalInfo::getInstance()->sdkURL = Configuration::getInstance()->getValue("sdkURL").asString();
    GlobalInfo::getInstance()->noSdkUrl = Configuration::getInstance()->getValue("noSdkURL").asString();
    GlobalInfo::getInstance()->version = Configuration::getInstance()->getValue("version").asString();

    
    SdkManager::getInstance()->channel = Configuration::getInstance()->getValue("channel").asString();
    //登陆服务器列表。顺着连
    if(GlobalInfo::getInstance()->isNativeMode)
    {
         GlobalInfo::getInstance()->domainList = StringUtil::split(Configuration::getInstance()->getValue("loginURLNative").asString(), ",");
        GlobalInfo::getInstance()->resourceDomainList = StringUtil::split(Configuration::getInstance()->getValue("nativeDataVersionDomain").asString(), ",");
    }
    else
    {
         GlobalInfo::getInstance()->domainList = StringUtil::split(Configuration::getInstance()->getValue("loginURLList").asString(), ",");
        GlobalInfo::getInstance()->resourceDomainList = StringUtil::split(Configuration::getInstance()->getValue("dataVersionDomain").asString(), ",");
    }
   

}
void LoginLayer::onSdkLoginSuc()
{
    if(GlobalInfo::getInstance()->uid == "")
    {
        UserLoginLayer::show();
    }
    else
    {
        if(this->getChildByTag(TAG_VIDEO))
        {
            this->removeChildByTag(TAG_VIDEO);
        }
        HttpURLManager::getInstance()->login();
    }
}
void LoginLayer::onMsgProcess(EventCustom* msg)
{
//    MessageReceive* message = (MessageReceive*)msg->getUserData();
  
}

void LoginLayer::enterStageBattle(int index)
{
//     GlobalInfo::getInstance()->stageBattleList.clear();
//    Vector<DictStageBattle*>* list = DictStageBattleManager::getInstance()->getDataList();
//    for(DictStageBattle* data : *list)
//    {
//        if(data->inStageId == 1)
//        {
//            GlobalInfo::getInstance()->stageBattleList.push_back(data->id);
//        }
//    }
//
//    sort(GlobalInfo::getInstance()->stageBattleList.begin(), GlobalInfo::getInstance()->stageBattleList.end());
//    GlobalInfo::getInstance()->battleType = kBattleType_MingZhanYi;
//   
//    if(index == 0)
//    {
//         NewPlayerGuild::getInstance()->start();
//    }
//    else if(index == 1)
//    {
//        NewPlayerGuild::getInstance()->onStageBattleOver(GlobalInfo::getInstance()->stageBattleList[0]);
//    }
//    BattleLoader::requestStageBattle(GlobalInfo::getInstance()->stageBattleList[index]);
}
void LoginLayer::onDialogConfirm(Node* pSender)
{
    auto scene = LoginLayer::createScene();
    // run
    Director::getInstance()->replaceScene(scene);
}

void LoginLayer::onResourceSuc(EventCustom* event)
{
    Dialog::showServerLoading(0);

}
void LoginLayer::onClientAppSuc(EventCustom* event)
{
    GlobalInfo::getInstance()->isEnterLogin = true;
    if(GlobalInfo::getInstance()->isShowGuide)
    {
        if(UserDefault::getInstance()->getBoolForKey("QIXI_ISLOADED", false) || GlobalInfo::getInstance()->isPlayedGuideBattle )
        {
            this->setVideo();
        }
        else
        {
            GlobalInfo::getInstance()->isPlayedGuideBattle = true;
            Scene* scene = LoginBattle::create();
            Director::getInstance()->replaceScene(scene);
        }
    }
    else
    {
        this->setVideo();
    }
    
    TDTalkDataManager::getInstance()->start();
}
//void LoginLayer::onChannalloginListern(YVSDK::ChanngelLonginRespond* r)
//{
//    GlobalInfo::getInstance()->chatChannelIsOk = true;
//    log("lskdjfl");
//}
void LoginLayer::addEventListener()
{
    
    this->addUserMsg(CUSTOM_SDK_LOGINSUC, CC_CALLBACK_0(LoginLayer::onSdkLoginSuc, this));
    this->addUserMsg(CUSTOM_SDK_LOGINCANCEL,CC_CALLBACK_0(LoginLayer::setLoginSdkBtn, this));

    this->addUserMsg(CUSTOM_RESOURCE_UPDATE_SUC, CC_CALLBACK_1(LoginLayer::onResourceSuc, this));
    this->addUserMsg(CUSTOM_CLIENTAPP_SUC, CC_CALLBACK_1(LoginLayer::onClientAppSuc, this));
   this->addUserMsg(CUSTOM_UPDATE_VERSION, CC_CALLBACK_1(LoginLayer::updateVersion, this));
    this->addUserMsg(CUSTOM_CONFIG_UPDATE_SUC, CC_CALLBACK_1(LoginLayer::loadConfigFile, this));
}
void LoginLayer::removeEventListener()
{
    
    BaseLayer::removeEventListener();
}
bool LoginLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}
void LoginLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    
}
void LoginLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
    if(GlobalInfo::getInstance()->isUpdateVersion )
    {
        Dialog::show("为了不影响您的体验，请更新最新版本！");
        return;
    }
    if(!GlobalInfo::getInstance()->isEnterLogin)
    {
        return;
    }
    if(this->getChildByTag(TAG_SDKBTN) || this->getChildByTag(TAG_VIDEO))
    {
        return;
    }
    Scene* scene = Director::getInstance()->getRunningScene();
    if(scene->getChildByTag(LAYER_ENTER_GAME))
    {
        return;
    }
    onLoginClick(NULL);
}
void LoginLayer::updateVersion(EventCustom* event)
{
    Label* label = (Label*)this->getChildByTag(TAG_VERSION);
    if(label)
    {
        label->setString(GlobalInfo::getInstance()->version);
    }
    else
    {
        label = PublicShowUI::getLabel(GlobalInfo::getInstance()->version.c_str(),Color3B::WHITE,25,true,true);
        label->setAnchorPoint(Point::ZERO);
        this->addChild(label,20,TAG_VERSION);
    }
    label->setPosition(VisibleRect::right().x - label->getContentSize().width, VisibleRect::bottom().y);
 
   
}