//
//  GlobalInfo.cpp
//
//
//  Created by zxb on 14-5-27.
//
//

#include "GlobalInfo.h"
#include "../AppMacros.h"
#include "../common/Dialog/Dialog.h"
#include "../common/StringUtil.h"
GlobalInfo* GlobalInfo::_instance = NULL;
GlobalInfo* GlobalInfo::getInstance()
{
    if(!_instance )
    {
        _instance =  new GlobalInfo();
    }
    return _instance;
}
GlobalInfo::~GlobalInfo()
{
    CC_SAFE_DELETE(mainSceneHeroList);
    mainSceneHeroList = NULL;
    CC_SAFE_DELETE(gameRole);
    gameRole = NULL;
}
void GlobalInfo::destroyInstance()
{
    if(_instance)
    {
        delete _instance;
        _instance = NULL;
    }
}
GlobalInfo::GlobalInfo()
:screenScaleX(1)
,screenScaleY(1)
,isShowReconnect(false)
,isReceivedDataEnabled(true)
,isNewEnterGame(false)
,addressIP("")
,nowServerID("")
,nowServerName("")
,version("")
,dictDataVersion("1463127558103")
,mainSceneHeroList(NULL)
,isPlayedGuideBattle(false)
,port(0)
,vipId(0)
,vipLevel(0)
,vipExp(0)
,isShowStoryTalk(true)
,bodyPower(0)
,userGold(0)
,userCopper(0)
,luckyLeftTime(0)
,chapterOpenStage(0)
,isInNewVillage(true)
,isFirstEnterMainScene(false)
,addictedLevel(0)
,addictedMsg("")
,map_tiled_width(0)
,map_tiled_height(0)
,bloodBottle(0)
,gameID("1")
,gamePackUrl("")
,isAutoDownClient(false)
,uid("")
,token("")
,sessionID("")
,gameSessionId("")
,isSdkMode(false)
,battleTimeScale(1)
,battleMode(kBattleModeUser)
,stageMode(kStageModeCommon)
,battleType(kBattleType_None)
,gameRole(NULL)
,deviceUUID("")
,_domainURL("")
,loginPort("")
,sdkURL("")
,noSdkUrl("")
,serverListURL("")
,subChannelActive("")
,dotStr("")
,subChannel("emind0")
,bodyPowerMax(0)
,taskInStageBattle(0)
,isShowGuide(true)
,isGuiding(false)
,isDebug(false)
,isEnterLogin(false)
,isNativeMode(true)
,curEquipCount(0)
,curHeroCount(0)
,maxHeroCount(0)
,equipCountLimit(0)
,m_mapScale(2)
,m_avatarScale(.5)
,raidsCard(0)
,firstRechargeStatus(1)
,sevendayActivity(0)
,isUpdateVersion(false)
,chatChannelIsOk(false)
,famouseBossID(0)
,famouseBossLevel(1)
,famouseName("")
,famousePeroid(0)
,famouseBossBlood(0)
,famouseLeftSeconds(0)
,famouseChallengeCount(0)
{
    gameRole = new RoleData();
    gameRole->mainHeroDictID = 113040;
    mainSceneHeroList = new Vector<RoleData*>();
    m_mapScale = m_mapScale * getMapScaleValue();
   
}
//初始化红点变量
void GlobalInfo::initDotList(string value)
{
    dotStr="0"+value;
    dotList = dotStr.c_str();
    
}
void GlobalInfo::initIs()
{
    isNewEnterGame = false;
    battleType = kBattleType_None;
    isUpdateVersion = false;
}
void GlobalInfo::setIsPlayBackMusic(bool enabled)//是否播放背景音乐
{
    UserDefault::getInstance()->setBoolForKey("isPlayBackMusic_SANGUO", enabled);
    UserDefault::getInstance()->flush();
}
bool GlobalInfo::getIsPlayBackMusic()
{
    bool enabled = UserDefault::getInstance()->getBoolForKey("isPlayBackMusic_SANGUO", true);
    return enabled;
}

void GlobalInfo::setIsPlayEffectMusic(bool enabled)
{
     UserDefault::getInstance()->setBoolForKey("isPlayEffectMusic_SANGUO", enabled);
    UserDefault::getInstance()->flush();
}
bool GlobalInfo::getIsPlayEffectMusic()//是否播放音效
{
     return UserDefault::getInstance()->getBoolForKey("isPlayEffectMusic_SANGUO", true);
}
float GlobalInfo::getMapScaleValue()
{
    Size winSizeInPixels = Director::getInstance()->getWinSize();
    int height = winSizeInPixels.height;
    log("1111111====%f",winSizeInPixels.height);
    if(height % 768 == 0)
    {
        return 1;
    }
    if(height % 320 == 0)
    {
        return .8;
    }
   
    return .8;
}


