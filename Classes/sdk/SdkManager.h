//
//  SdkManager.h
//  SuiTang
//
//  Created by zhangxiaobin on 15/4/14.
//
//

#ifndef __SuiTang__SdkManager__
#define __SuiTang__SdkManager__


#include "cocos2d.h"
USING_NS_CC;

#include <network/HttpRequest.h>
#include <network/HttpResponse.h>
#include <network/HttpClient.h>


#define ENTER_SERVER "enterServer"
#define LEVELUP "levelUp"
#define CREATE_ROLE "createRole"


class SdkManager:public Ref
{
public:
    static SdkManager* getInstance();
    static void destoryInstance();
    std::string channel;
    std::string channelName;
    std::string channelUserID;
    std::string channelUserName;
    std::string productCode;
    std::string appid;
public:
    void initSDK();
    void startLogin();
    void changeUser();//切换用户
    void startLogout();//注销用户
    void startExit();
    void showExitDialog();///显示退出游戏确定框
  
    bool isUserLogin();//是否已经登陆
    void debugEnable();

   
    void setUserExtData(const char* _ID);//设置玩家扩展数据
    void requestChargeOrder(int chargeType,int goldPackID,int cardID,int moneyNum);//请求订单编号
    void startCharge(const char* orderID,const char* info,const char* callBackUrl);//不定额支付开始充值
    void createOrder(int count,const char* info,int moneyNum,const char* unitName,const char* callbackUrl);//定额支付
    void checkOrder(const char* orderID);
    void presentUserCenter();
    void checkNewVersion();
    //接收回调--登录相关
    virtual void onLoginSuc(const char *uid,const char *token,const char* channel );
    virtual void onLoginCanceled();
    virtual void onLoginLogout();
    virtual void onExit();
    //接收回调--支付相关
    virtual void onPaySuccessOfOrder(const char* orderSerial, const char* orderName, const char* body,double price, const char* userParam);
    virtual void onPayFailOfOrder(const char* orderSerial, const char* orderName, const char* body,double price, const char* userParam, int errorid);
    virtual void onPayCancelOfOrder(const char* orderSerial, const char* orderName, const char* body,double price,const char* userParam);
    
    //接收回调--订单相关
    virtual void checkDoneOfOrder(const char* orderSerial, double price, int status);
    virtual void checkFailedOfOrder(const char* orderSerial);
    virtual void checkNewVersionDone(bool hasNewVersion,bool mustUpdate);

  
private:
    static SdkManager* _instance;
    SdkManager();
    ~SdkManager();
    void onDialogClick(Node* pSender);
    bool isInited;//是否已经初始化
   
};

#endif /* defined(__SuiTang__SdkManager__) */
