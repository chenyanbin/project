//
//  AuctionSahngjiaCellLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/15.
//
//

#ifndef __FightPass__AuctionSahngjiaCellLayer__
#define __FightPass__AuctionSahngjiaCellLayer__


#include "../../../BaseLayer.h"
#include "../../marketData/auctionData/AuctionShangjiaData.h"
class AuctionSahngjiaCellLayer:public BaseLayer
{
public:
    AuctionSahngjiaCellLayer();
    ~ AuctionSahngjiaCellLayer();
    virtual bool init(int idx);
    static AuctionSahngjiaCellLayer* create(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void shangjiaCellBackGround(int idx);
    void Updata(float dt);
    void onClick(Ref* psender);
    void onitemHeadClick(Node* pSender);
    void requestAuctionsahngjiaListMsg(int lastMarketGoodsId);
    void onTipsStateMsg(EventCustom* msg);
    void addEventListener();
    void removeEventListener();
private:
    int TAG_SHANGJAITIME;//倒计时时间
    long m_shangjiatimess;//倒计时的时间
    Label* m_shangjiatimeLabel;
    bool istips;
};


#endif /* defined(__FightPass__AuctionSahngjiaCellLayer__) */
