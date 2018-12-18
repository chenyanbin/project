//
//  AuctionSureXiajiaLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/25.
//
//

#ifndef __FightPass__AuctionSureXiajiaLayer__
#define __FightPass__AuctionSureXiajiaLayer__

#include "../../../BaseLayer.h"
class AuctionSureXiajiaLayer:public BaseLayer
{
public:
    AuctionSureXiajiaLayer();
    ~ AuctionSureXiajiaLayer();
    virtual bool init(int findId);
    static AuctionSureXiajiaLayer* create(int itemId);
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
    
    void requestSurexiajiaMsg(int SellId);//请求下架
    void onSureXiajiaProcess(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    int m_itemId;//购买物品的sellId
    
    
};


#endif /* defined(__FightPass__AuctionSureXiajiaLayer__) */
