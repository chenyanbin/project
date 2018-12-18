//
//  MarketPurchaseLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/27.
//
//

#ifndef __FightPass__MarketPurchaseLayer__
#define __FightPass__MarketPurchaseLayer__

#include "../../BaseLayer.h"
#include "../../data/BaseTypeData.h"
class MarketPurchaseLayer:public BaseLayer
{
public:
    enum TAG_BTN
    {
        TAG_ADD = 10,
        TAG_ADDTEN,
        TAG_MINUS,
        TAG_MINUSTEN
    };
    MarketPurchaseLayer();
    ~MarketPurchaseLayer();
    virtual bool init(int idx);
    static MarketPurchaseLayer* create(int idx);
    static void show(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setButton();
    void setPrice(int nowCount);
    void onBuyclick(Ref* psender);
    void setSureBuyBtn();
    void onCencelClick(Ref* psender);
    void onSureBuyClick(Ref* psender);
    
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestListMsg(int shopId ,int count );//发送购买信息
private:
    int m_nowcount;
    int TAG_COUNT;
    int TAG_ALLCOUNT;
    int allPrice;//总价格
    int m_idx;//售卖物品角标
    int TAG_GOLD;
    
    Vector<BaseTypeData*>* m_baselist;
};

#endif /* defined(__FightPass__MarketPurchaseLayer__) */
