//
//  LuxurySignin_Layer.h
//  FightPass
//
//  Created by 超 顾 on 15/10/12.
//
//

#ifndef __FightPass__LuxurySignin_Layer__
#define __FightPass__LuxurySignin_Layer__

#include "extensions/cocos-ext.h"
#include "cocos2d.h"
#include "../../../BaseLayer.h"
#include "../everydaySignin/EverydaySignin_Layer.h"
#include "../../../data/BaseTypeData.h"
USING_NS_CC_EXT;
USING_NS_CC;
class LuxurySignin_Layer:public BaseLayer
{
public:
    LuxurySignin_Layer();
    ~LuxurySignin_Layer();
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual bool init();
    static LuxurySignin_Layer* create();
private:
    void createLayer();
    void onComboBoxBtnClick(Ref* psender);
    void onBtnClick(Ref* psender);
    void addEventListener();
    void removeEventListener();
    void onMsgProcess(EventCustom* msg);
    void onUserTipsClick(Node* pSender);
    void onCreateStatus();
    
    void requestListMsg();
    void requestListGetMsg();
private:
    float sx;
    vector<SigninData*> *m_list;
    int m_day;
    int m_status;
    int TAG_PRIZE;
    int TAG_RECHARGE;//充值
    Vector<BaseTypeData*> *m_baseList;
};

#endif /* defined(__FightPass__LuxurySignin_Layer__) */
