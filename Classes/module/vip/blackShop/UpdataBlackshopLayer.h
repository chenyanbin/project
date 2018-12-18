//
//  UpdataBlackshopLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/10/15.
//
//

#ifndef __FightPass__UpdataBlackshopLayer__
#define __FightPass__UpdataBlackshopLayer__

#include "../../BaseLayer.h"

class UpdataBlackshopLayer:public BaseLayer
{
public:
    UpdataBlackshopLayer();
    ~ UpdataBlackshopLayer();
    virtual bool init(int needGold);
    static UpdataBlackshopLayer* create(int needGold);
    static void show(int needGold);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void setUiSpr();
    void setSureBuyBtn();
    void onSureBuyClick(Ref* psender);
    void onCencelClick(Ref* psender);    
private:
    int m_needGold;//刷新消耗元宝
    
    
};


#endif /* defined(__FightPass__UpdataBlackshopLayer__) */
