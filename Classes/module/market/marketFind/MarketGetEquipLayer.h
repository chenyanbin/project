//
//  MarketGetEquipLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/6.
//
//

#ifndef __FightPass__MarketGetEquipLayer__
#define __FightPass__MarketGetEquipLayer__

#include "../../BaseLayer.h"
class MarketGetEquipLayer:public BaseLayer
{
public:
    MarketGetEquipLayer();
    ~MarketGetEquipLayer();
    virtual bool init();
    static MarketGetEquipLayer* create();
    static void show();
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
protected:
    virtual void backScene();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void setBackg();
    void setCardItem();
    void onClick(Ref* psender);
    void onHeadClick(Node* pSender);
private:
    int m_allGoods;
    bool m_iscloseScene;
};


#endif /* defined(__FightPass__MarketGetEquipLayer__) */
