//
//  MarketGoodsLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/5.
//
//

#ifndef __FightPass__MarketGoodsLayer__
#define __FightPass__MarketGoodsLayer__
#include "../marketData/MarketFindResultDataManager.h"
#include "../../BaseLayer.h"
class MarketGoodsLayer:public BaseLayer
{
public:
    MarketGoodsLayer();
    ~MarketGoodsLayer();
    virtual bool init(bool _bol);
    static MarketGoodsLayer* create(bool _bol=true);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void backScene();
private:
    void settitle();
    void showItem();
    void showHeroEffect(MarketFindResultData* finddata);
    void onClick(Ref* pSender);
    void onHeroHeadClick(Node* pSender);
    
    void setHeroPos(MarketFindResultData* data);
protected:
    
private:
    int m_nowIndex;
    bool m_bol;
    int m_headIndex;
    const char* m_path;
    int m_quality;
    
};
#endif /* defined(__FightPass__MarketGoodsLayer__) */
