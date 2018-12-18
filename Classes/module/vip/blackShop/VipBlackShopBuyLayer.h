//
//  VipBlackShopBuyLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/16.
//
//

#ifndef __FightPass__VipBlackShopBuyLayer__
#define __FightPass__VipBlackShopBuyLayer__

#include "../../BaseLayer.h"
#include "../../data/BaseTypeData.h"
class VipBlackShopBuyLayer:public BaseLayer
{
public:
    enum TAG_BTN
    {
        TAG_ADD = 10,
        TAG_ADDTEN,
        TAG_MINUS,
        TAG_MINUSTEN
    };
    VipBlackShopBuyLayer();
    ~ VipBlackShopBuyLayer();
    virtual bool init(int idx);
    static VipBlackShopBuyLayer* create(int idx);
    static void show(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setButton();
    void setSureBuyBtn();
    void onCencelClick(Ref* psender);
    void onSureBuyClick(Ref* psender);
    
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg(int shopId );//发送购买信息
private:
    int m_nowcount;
    int TAG_COUNT;
   
    int allPrice;//总价格
   
    int m_idx;//售卖物品角标
    Vector<BaseTypeData*>* m_baselist;
   
};

#endif /* defined(__FightPass__VipBlackShopBuyLayer__) */
