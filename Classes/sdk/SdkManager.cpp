//
//  SdkManager.cpp
//  SuiTang
//
//  Created by zhangxiaobin on 15/4/14.
//
//
#include "../common/GameConfig.h"
#include "../tdTalkData/TDTalkDataManager.hpp"
#include "SdkManager.h"
#include "SdkCallBackProxy.h"
#include "../protocol/UserCustomEvent.h"
#include "../commonData/GlobalInfo.h"
#include "../net/NetworkDataProcessing.h"
#include "../common/PublicShowUI.h"
#include "../common/StringUtil.h"
#include "../common/Dialog/Dialog.h"
#include "../message/Decoding/recharge/RequestRechargeOrder.h"
#include "../net/NetworkDataProcessing.h"
#include "../module/login/serverList/ServerListDataManager.h"
#include "../protocol/UserCustomEvent.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <dirent.h>
#include <sys/stat.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include <platform/android/jni/JniHelper.h>
#include <android/log.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif
#endif

SdkManager* SdkManager::_instance = NULL;


SdkManager::SdkManager():isInited(false)
,channel("")
,channelUserID("")
,productCode("")
,appid("{0E2306A6-004DA3E4}")
,channelUserName("")
,channelName("")
{
    
}
SdkManager::~SdkManager()
{
 
}
SdkManager* SdkManager::getInstance()
{
    if(!_instance)
    {
        _instance = new SdkManager();
    }
    return _instance;
}
void SdkManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}

//初始化PaySDK
void SdkManager::initSDK()
{
    log("------------------------------初始化sdk-------------------------------");
    if(!isInited)
    {
        log("GlobalInfo::getInstance()->isSdkMode=%d",GlobalInfo::getInstance()->isSdkMode);
        if(GlobalInfo::getInstance()->isSdkMode)
        {
            
            SFGameNativeInterface::setInitCallback(new SFNativeOnlineInitCallbackImpl());
            SFGameNativeInterface::setLoginCallback(new SFNativeOnlineLoginCallbackImpl());
            SFGameNativeInterface::setPayResultCallback(new SFNativeOnlinePayResultCallbackImpl());
            SFGameNativeInterface::setExitCallback(exitCallback);
            SdkManager::getInstance()->channelName = PublicShowUI::getSelfChannelLabel();
          
            #if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                  SFGameNativeInterface::onCreate();
            #endif
           
           
            
            log("------------------------------初始化isInited ==true-------------------------------");
        }
        else
        {
            Scene* scene = LoginLayer::createScene();
            // run
            Director::getInstance()->runWithScene(scene);
         
        }
        isInited = true;
    }
    else
    {
    
    }
        log("------------------------------初始化sdk2222222222-------------------------------");
}

//开始登录
void SdkManager::startLogin()
{
 
    if(GlobalInfo::getInstance()->isSdkMode)
    {
        if(!isInited)
        {
            initSDK();
        }
        #if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            SFGameNativeInterface::login("login");
        #endif
        #if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
             SFGameNativeInterface::login("login");
        #endif
    
    }
    else
    {
        onLoginSuc("","111111111","emind");
    }
   
}

//切换账号
void SdkManager::changeUser() {
    
}

//注销
void SdkManager::startLogout()
{
    if(GlobalInfo::getInstance()->isSdkMode)
    {
        onLoginLogout();
    }
    else
    {
        onLoginLogout();
    }
    
}
void SdkManager::startExit()
{
    if(GlobalInfo::getInstance()->isSdkMode)
    {
        SFGameNativeInterface::exit();
    }
    else
    {
         onExit();
    }
}
void SdkManager::showExitDialog()
{
      Dialog::show("主公确定要退出吗？","",2,this,callfuncN_selector(SdkManager::onDialogClick));
}
void SdkManager::onDialogClick(Node* psender)
{
    if(psender->getTag() == 1)
    {
         SdkManager::getInstance()->onExit();
    }
}

//是否登录
bool SdkManager::isUserLogin() {
    return false;

}

//打印日志
void SdkManager::debugEnable() {
   
}

void SdkManager::requestChargeOrder(int chargeType,int goldPackID,int cardID,int moneyNum)
{
    Dialog::showServerLoading(1);
    moneyNum = moneyNum * 100;//转换为分
    RequestRechargeOrder* msg = new RequestRechargeOrder(chargeType,goldPackID,cardID,moneyNum);
    NetworkDataProcessing::getInstance()->sendMessage(msg);
    msg = NULL;
}
//开始充值 不定额支付
void SdkManager::startCharge(const char* orderID,const char* info,const char* callBackUrl)
{

    SFGameNativeInterface::charge("元宝", 500, 1, info, callBackUrl);
    
}
void SdkManager::setUserExtData(const char* _ID)//设置玩家扩展数据
{
    //    _id 当前情景，请根据相应场景选择后面的场景类型，目前支持 enterServer （进入服务器），levelUp （玩家升级），createRole （玩家创建角色
    //    roleId 当前登录的玩家角色ID，必须为数字，若无，传入userid
    //    roleName 当前登录的玩家角色名，不能为空，不能为null，若无，传入”游戏名称+userId”
    //    roleLevel 当前登录的玩家角色等级，必须为数字，若无，传入1
    //    zoneId 当前登录的游戏区服ID，必须为数字，若无，传入1,若游戏分区服，请不要传入固定写死的ID，否则会造成渠道退包
    //    zoneName 当前登录的游戏区服名称，不能为空，不能为null，若无，传入 “游戏名称+1服”，若游戏分区服，请不要传入固定写死的区服名，否则会造成渠道退包
    //    balance 当前用户游戏币余额，必须为数字，若无，传入0 经确定 是指的金币
    //    vip 当前用户VIP等级，必须为数字，若无，传入1
    //    partyName 当前用户所属帮派，不能为空，不能为null，若无，传入”无帮派”
    
    if(!GlobalInfo::getInstance()->isSdkMode)
    {
        return;
    }
    string roleID = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->roleID);
    string roleName = GlobalInfo::getInstance()->gameRole->name;
    string roleLevel = PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->level);
    //    string jsonStr = "{";
//    string _id = PublicShowUI::makeJosnData("_id",_ID);
//    string roleId = PublicShowUI::makeJosnData("roleId" ,PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->roleID).c_str());
//    string roleName = PublicShowUI::makeJosnData("roleName" ,GlobalInfo::getInstance()->gameRole->name.c_str());
//    
//    string roleLevel = PublicShowUI::makeJosnData("roleLevel" ,PublicShowUI::numberToString(GlobalInfo::getInstance()->gameRole->level).c_str());
//    string zoneId = PublicShowUI::makeJosnData("zoneId" , GlobalInfo::getInstance()->nowServerID.c_str()) ;
//    string zoneName = PublicShowUI::makeJosnData("zoneName" ,GlobalInfo::getInstance()->nowServerName.c_str());
//    
//    char str[50] = {"0"};
//    sprintf(str, "%.0f",GlobalInfo::getInstance()->userGold);
//    
//    string balance = PublicShowUI::makeJosnData("balance" ,str);
//    string vip = PublicShowUI::makeJosnData("vip" ,PublicShowUI::numberToString(GlobalInfo::getInstance()->vipLevel).c_str());
//    string guildName =  "无帮派";
//    string partyName = PublicShowUI::makeJosnData("partyName" ,guildName.c_str());
//    
//    jsonStr = jsonStr + _id + "," + roleId +"," + roleName + "," + roleLevel + "," + zoneId + "," + zoneName + "," + balance + "," +vip  +  "," +partyName + "}";
//    log("jsonStr ==%s",jsonStr.c_str());
    
//    GameProxy::SetExtRoleData(jsonStr.c_str());
    SFGameNativeInterface::setRoleData(roleID.c_str(), roleName.c_str(), roleLevel.c_str(), "不存在", "不存在");
}
//定额支付
void SdkManager::createOrder(int moneyNum,const char* info,int count,const char* unitName,const char* callbackUrl)
{
    /* pay定额计费接口
     * static void pay(int unitPrice, const char*  unitName,
     * 		int count, const char*  callBackInfo, const char* callBackUrl);
     *
     *  @param unitPrice     当前商品需要支付金额，单位为人民币分
     *  @param itemName      虚拟货币名称
     *  @param count         用户选择购买道具界面的默认道具数量。（总价 count*unitPrice）
     *  @param callBackInfo  由游戏开发者定义传入的字符串，会与支付结果一同发送给游戏服务器，游戏服务器可通过该字段判断交易的详细内容（金额角色等）
     *  @param callBackUrl   将支付结果通知给游戏服务器时的通知地址url，交易结束后，系统会向该url发送http请求，通知交易的结果金额callbackInfo等信息
     */

        SFGameNativeInterface::pay(moneyNum, unitName, count, info, callbackUrl);


}

//查询订单状态
void SdkManager::checkOrder(const char* orderID)
{
    
}

//展示用户中心
void SdkManager::presentUserCenter()
{
}

//检查更新
void SdkManager::checkNewVersion()
{
    
}
#pragma mark --- 所有回调如下 ---

void SdkManager::onLoginSuc(const char *uid,const char *token,const char* channel)
{
     Dialog::hideServerLoading();
    log("SdkManager::onLoginSuc SdkManager::onLoginSuc");
//    string tt = token;
//    token = StringUtil::replace(tt," " ,"").c_str();
    GlobalInfo::getInstance()->uid = uid;
    GlobalInfo::getInstance()->token = token;
    SdkManager::getInstance()->channel = channel;
    
    
    PublicShowUI::broadUserMsg(CUSTOM_SDK_LOGINSUC, NULL);

    
    
//    if(StringUtil::split(channel, "lj").size() > 0)
//    {
//           PublicShowUI::getSelfChannelLabel();
//    }
 
 

}
void SdkManager::onLoginCanceled()
{
    log("登陆取消");
    Dialog::hideServerLoading();
    GlobalInfo::getInstance()->uid = "";
    GlobalInfo::getInstance()->token = "";

}

void SdkManager::onLoginLogout()
{
    log("注销成功");
    Dialog::hideServerLoading();
    GlobalInfo::getInstance()->uid = "";
    GlobalInfo::getInstance()->token = "";
    if(Director::getInstance()->getRunningScene()->getChildByTag(SCENE_TAG_LOADING))
    {
        log("在登陆界面注销");
        NetworkDataProcessing::sharedNet()->closeNet();
        PublicShowUI::broadUserMsg(CUSTOM_SDK_LOGINCANCEL, NULL);
    }
    else
    {
        log("在游戏界面注销");
        NetworkDataProcessing::sharedNet()->reLogin();
    }
   
}
void SdkManager::onExit()
{
    if(GlobalInfo::getInstance()->isSdkMode)
    {
      
    }
    NetworkDataProcessing::getInstance()->closeNet();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
        return;
    #endif
        Director::getInstance()->end();
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}
void SdkManager::onPaySuccessOfOrder(const char* orderSerial, const char* orderName, const char* body,double price, const char* userParam)
{
    
    std::string oid = orderSerial;
    std::string str = "支付成功，订单号："+ oid + "\n";
//     MessageBox("", str.c_str());
    log("str==%s",str.c_str());
    TDTalkDataManager::getInstance()->onChargeSuc(orderSerial);
}

void SdkManager::onPayFailOfOrder(const char* orderSerial, const char* orderName, const char* body,double price, const char* userParam, int errorid)
{
    std::string oid = orderSerial;
    std::string str = "支付失败，订单号："+ oid + "\n";
    MessageBox("", str.c_str());
//    std::string msg = messageLabel->getString();
//    std::string oid = orderSerial;
//    messageLabel->setString("Demo：支付失败，订单号："+ oid + "\n" + msg);
    
    TDTalkDataManager::getInstance()->onChargeFailed(orderSerial);
}

void SdkManager::onPayCancelOfOrder(const char* orderSerial, const char* orderName, const char* body,double price,const char* userParam)
{
    std::string oid = orderSerial;
    std::string str = "支付取消，订单号："+ oid + "\n";
    MessageBox("", str.c_str());
//    std::string msg = messageLabel->getString();
//    std::string oid = orderSerial;
//    messageLabel->setString("Demo：支付取消，订单号："+ oid + "\n" + msg);
     TDTalkDataManager::getInstance()->onChargeFailed(orderSerial);
}

void SdkManager::checkDoneOfOrder(const char* orderSerial, double price, int status)
{
//    std::string msg = messageLabel->getString();
//    std::string oid = orderSerial;
//    std::ostringstream end;
//    end<<"Demo：订单查询成功，订单号：";
//    end<<oid;
//    end<<" 金额：";
//    end<<price;
//    end<<" 状态：";
//    end<<status;
//    end<<"\n";
//    end<<msg;
//    
//    messageLabel->setString(end.str());
}

void SdkManager::checkFailedOfOrder(const char* orderSerial)
{
//    std::string msg = messageLabel->getString();
//    std::string oid = orderSerial;
//    messageLabel->setString("Demo：订单查询失败，订单号："+ oid + "\n" + msg);
}

void SdkManager::checkNewVersionDone(bool hasNewVersion,bool mustUpdate)
{
    //此回调暂时无用
}


