//
//  SdkCallBackProxy.h
//  FightPass
//
//  Created by zhangxiaobin on 15/10/15.
//
//

#ifndef SdkCallBackProxy_h
#define SdkCallBackProxy_h
#include "cocos2d.h"
#include "SdkManager.h"
#include "../common/noticeManager/NoticeManager.h"
#include "../common/Dialog/Dialog.h"
#include "../SFGameNativeInterface.hpp"
#include "../module/login/LoginLayer.h"
#include "../common/StringUtil.h"

class SFNativeOnlineLoginCallbackImpl: public SFNativeOnlineLoginCallback
{
public:
    SFNativeOnlineLoginCallbackImpl()
    {
    }
    
    /*SDK账户登出，如有游戏有账户切换功能，可在此做再次登陆操作*/
    virtual void onLogout(const char* remain)
    {
       log("1111   onLogout onLoginSuccessonLogout=%s",remain);
        SdkManager::getInstance()->onLoginLogout();
    }
    
    /*SDK登陆成功回调，此回调为客户端返回，需要去游戏服务器验证是否真正登陆成功*/
    virtual void onLoginSuccess(SFNativeOnlineUser* user, const char* remain)
    {
        
        log("1111   onLoginSuccess onLoginSuccess =%s",user->channelUserId);
        SdkManager::getInstance()->productCode = user->productCode;
       SdkManager::getInstance()->channelUserName = user->userName;
        if(SdkManager::getInstance()->channelUserID.size() > 0)
        {
            if(SdkManager::getInstance()->channelUserID != user->channelUserId)
            {
             
                SdkManager::getInstance()->channelUserID = user->channelUserId;
                SdkManager::getInstance()->onLoginLogout();
                return;
            }
          
        }
        SdkManager::getInstance()->channelUserID = user->channelUserId;
        SdkManager::getInstance()->onLoginSuc(user->channelUserId,user->token,user->channelId);
    }
    
    /*登陆失败回调*/
    virtual void onLoginFailed(const char* r, const char* remain)
    {
       SdkManager::getInstance()->onLoginCanceled();
    }
  
    void callLogin(float fDelta)
    {
//        SFGameNativeInterface::login("login");
    }
};


/*游戏退出回调类*/
class SFNativeOnlineExitCallbackImpl: public SFNativeOnlineExitCallback {
    /*SDK没有退出界面时，走此方法，可以自定义退出界面*/
    virtual void onNoExiterProvide() {
       SdkManager::getInstance()->onExit();
    }
    
    /*SDK有退出界面时调用此方法
     * result
     * 		true：退出
     * 		false：取消退出*/
    virtual void onSDKExit(bool result) {
        if (!result)
            return;
        SdkManager::getInstance()->onExit();
    }
    
};
class SFNativeOnlineInitCallbackImpl: public SFNativeOnlineInitCallback
{
    virtual void onResponse(const char* tag, const char* remain)
    {
        log("on init Response==tag==%s, remain=%s",tag,remain);
           if(strcmp(tag,"success") != 0)
           {
               NoticeManager::getInstance()->showNotice("初始化失败");
           }
        else
        {
            Scene* scene = LoginLayer::createScene();
            // run
            Director::getInstance()->runWithScene(scene);
        }
    
    }
};


class SFNativeOnlinePayResultCallbackImpl: public SFNativeOnlinePayResultCallback {
    
    virtual void onFailed(const char* remain) {
        log("onFailed onFailed");
//        Dialog::show("充值失败");
    }
    virtual void onSuccess(const char* remain) {
        log("on pay sucess==%s",remain);
//        Dialog::show("充值成功");
        SdkManager::getInstance()->onPaySuccessOfOrder("","","",0,"");
  
    }
    virtual void onOderNo(const char* orderNo) {
        log("onOderNo onOderNo =%s",orderNo );
//         Dialog::show("orderNo ＝%s",orderNo);
    }
    
};

SFNativeOnlineExitCallbackImpl* exitCallback = new SFNativeOnlineExitCallbackImpl();

#endif /* SdkCallBackProxy_h */
