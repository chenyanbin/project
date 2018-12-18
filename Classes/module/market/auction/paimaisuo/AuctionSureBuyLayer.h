//
//  AuctionSureBuyLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/10.
//
//

#ifndef __FightPass__AuctionSureBuyLayer__
#define __FightPass__AuctionSureBuyLayer__

#include "../../../BaseLayer.h"
#include "../../../data/BaseTypeData.h"
class AuctionSureBuyLayer:public BaseLayer
{
public:
    AuctionSureBuyLayer();
    ~AuctionSureBuyLayer();
    virtual bool init(int findId);
    static AuctionSureBuyLayer* create(int itemId);
    static void show(int itemId);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUiSpr();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);
    
    void requestSureBuyMsg(int SellId);//请求购买
    void onSureBuyMsgProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
    
private:
    int m_itemId;//购买物品的sellId
    int m_owngold;//总元宝
    
    Vector<BaseTypeData*>* m_baseList;
    
    
};

#endif /* defined(__FightPass__AuctionSureBuyLayer__) */
