//
//  ServerLoadingLayer.h
//  SuiTang
//
//  Created by zhangxiaobin on 15/1/14.
//服务器通讯loaing 不让玩家重复操作
//

#ifndef __SuiTang__ServerLoadingLayer__
#define __SuiTang__ServerLoadingLayer__
#include "cocos2d.h"
USING_NS_CC;
#include "../../module/BaseLayer.h"
class ServerLoadingLayer:public BaseLayer
{
public:
    ServerLoadingLayer();
    ~ServerLoadingLayer();
    virtual bool init(float timess);
    static ServerLoadingLayer* create(float timess);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    bool isShowReLogin;//如果服务器没返回，是否显示重连
private:
    void leftHandHit();
    void rightHandHit();
    void initLoading();
    void setLoadingDot();
    void onDelay(float dt);
    void onDialogEvent(Node* pSender);
private:
    int TAG_CONNECTWORD;
    float delayTimes;
    Node* m_dotContainer;
    
    int TAG_LEFTHAND;
    int TAG_RIGHTHAND;
};


#endif /* defined(__SuiTang__ServerLoadingLayer__) */
