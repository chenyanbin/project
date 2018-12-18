//
//  VipLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/8.
//
//

#ifndef __FightPass__VipLayer__
#define __FightPass__VipLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "recharge/RechargeLayer.h"

class VipLayer:public BaseLayer
{
public:
    enum TAG_LAYER
    {
        TAG_RECHARGE = 1,
        TAG_LIBAO,
        TAG_BLACKSHOP,
    };
    VipLayer();
    ~ VipLayer();
    virtual bool init();
    static VipLayer* create();
    static void show(int fromScene,int openLayer = TAG_RECHARGE);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    void setInitOpenLayer(int layerTag);
private:
    void setbackGround();
    void setUserWealth();    
    void addRechargeLayer();
    void addbBlackshopLayer();
    void addLibaoLayer();
    void setVipLevel();
    void setheroPos();
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void onTequanCleck(Ref* psender);
    
    void combobox();
    void onComboBoxBtnClick(Ref* psender);
    void selectLayer(int tag);
    void onBtnClick(Ref* psender);
    
    void requestRechargePageMsg();//请求vip充值消息协议
    void onMsgProcess(EventCustom* message);
    void onRefreshDot(EventCustom* msg);
private:
    int m_tagLayer;
    int TAG_NAMEBG;
    int TAG_BLACKSHOPBG;
    int TAG_RECHARGEBG;
    int TAG_LIBAOBG;
    int TAG_VIPNODE;
    
    
    Sprite* m_selected;
    Vector<Button*>* btnList;
    Vector<CardData*>* cardList;
    
    int TAG_COMBOBOX;//按钮
    int TAG_SELECTED;//按钮框
    int TAG_MODULE;
    int TAG_MODULELABEL;
    float m_curVipExp;    //当前vip经验
    float m_totalVipTotal;//当前vip总经验
    Vector<ChargeStatusData*>* m_chargetstatesdata;
    int TAG_NODEBUTTON;
};


#endif /* defined(__FightPass__VipLayer__) */
