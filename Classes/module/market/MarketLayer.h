//
//  MarketLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/3.
//招慕
// 集市层

#ifndef __FightPass__MarketLayer__
#define __FightPass__MarketLayer__

#include "cocos2d.h"
#include "../BaseLayer.h"
#include "../../common/comboxBtn/ComboBoxBtn.h"
class MarketLayer:public BaseLayer
{
public:
    enum TAG_LAYER
    {
        TAG_XUNFANG = 1,
        TAG_JUXIAN ,
        TAG_SHANGDIAN,
        TAG_PAIMAI,
        TAG_LIBAP,//礼包
        TAG_BLACKSHOP,//黑市
        TAG_NAMEXUNFANG,
        TAG_NAMEJUXIAN,
        TAG_NAMESHAGNDIAN,
        TAG_NAMEPAIMAI,
        TAG_NAMELIBAOBG,
        TAG_NAMEBLACKSHOPBG,
        TAG_LIBAOHERO
    };
    MarketLayer();
    ~MarketLayer();
    virtual bool init();
    static MarketLayer* create();
    static void show(int fromScene,int openLayer = TAG_XUNFANG);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    void setInitOpenLayer(int layerTag);
private:
    void setbackGround();
    void setUserWealth();
    void setRightBtn();
    void onRightBtnClick(Ref* psender);
    void addxunfangLayer();
    void addjuxianLayer();
    void addshangdianLayer();
    void addpaimaiLayer();
    void addLibapLayer();
    void addBlackShopLayer();
    
    virtual void addEventListener();
    virtual void removeEventListener();

    void oncreateTenItemMsg(EventCustom* msg);//十连抽
    void onRefreshDot(EventCustom* msg);//刷新红点
private:
    int m_tagLayer;
    int TAG_NAMEBG;
    int TAG_SHOPBG;//商店
    int TAG_PAIMAIBG;//拍卖
    int TAG_JUXIANBG;//举贤
    ComboBoxBtn* boxBtn;
};

#endif /* defined(__FightPass__MarketLayer__) */
