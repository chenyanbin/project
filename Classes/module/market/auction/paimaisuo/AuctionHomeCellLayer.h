//
//  AuctionHomeCellLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/11.
//
//

#ifndef __FightPass__AuctionHomeCellLayer__
#define __FightPass__AuctionHomeCellLayer__

#include "../../../BaseLayer.h"
#include "../../marketData/auctionData/AuctionHomeData.h"
class AuctionHomeCellLayer:public BaseLayer
{
public:
    AuctionHomeCellLayer();
    ~ AuctionHomeCellLayer();
    virtual bool init(int idx);
    static AuctionHomeCellLayer* create(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void CellBackGround(int idx);
    void onHeroHeadClick(Node* psender);
    void oncellClick(Ref* psender);
    void Updata(float dt);
    void onClick(Ref* psender);
private:
    int TAG_TIME;//倒计时时间
    long timess;//倒计时的时间
    Label* timeLabel;
};


#endif /* defined(__FightPass__AuctionHomeCellLayer__) */
