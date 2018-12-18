//
//  LoginLayer.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/8.
//
//

#ifndef __FightPass__LoginLayer__
#define __FightPass__LoginLayer__

#include "../BaseLayer.h"
using namespace std;
using namespace cocos2d;
class LoginLayer:public BaseLayer
{
public:
    LoginLayer();
    ~LoginLayer();
    virtual bool init();
    void initPage();
    CREATE_FUNC(LoginLayer);
    static Scene* createScene(int fromeScene = SCENE_TAG_INIT);
    void setBackground();
    
    static void requestEnterGameMsg();
    static void enterMainUI();
    
  
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();

    void onMsgProcess(EventCustom* msg);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
//    void onCPLoginListern(YVSDK::CPLoginResponce*);
//    void onYYLoginListern(YVSDK::LoginResponse*);
//    void onGetCpuUserListern(YVSDK::GetCpmsgRepond*);
//    void onChannalloginListern(YVSDK::ChanngelLonginRespond*);
    void delaytime(float dt);
private:
    void setLoginSdkBtn();
    void onLoginClick(Ref* pSender);
    void loadConfigFile(EventCustom* event = NULL);
    void initInfoPlist();
  
    void onSdkLoginSuc();
    void onDialogConfirm(Node* pSender);
    void updateVersion(EventCustom* event = NULL);
    void onResourceSuc(EventCustom* event);
    void onClientAppSuc(EventCustom* event);
    void onStartLogin();
    void enterStageBattle(int index);
    void addAssetsLoading();
    void onVideFinished(Ref* target);
    void setVideo();
private:
    int TAG_SDKBTN;
    int TAG_VERSION;
    int TAG_VIDEO;
 
};

#endif /* defined(__FightPass__LoginLayer__) */
