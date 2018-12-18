//
//  FindCellLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/9/16.
//
//

#ifndef __FightPass__FindCellLayer__
#define __FightPass__FindCellLayer__

#include "../../BaseLayer.h"
#include "../marketData/MarketFindData.h"
class FindCellLayer:public BaseLayer
{
public:
    FindCellLayer();
    ~ FindCellLayer();
    virtual bool init(int idx);
    static FindCellLayer* create(int idx);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void shangjiaCellBackGround(int idx);
    void Updata(float dt);
    void onjiasuClick(Ref* psender);
    void againRequestListMsg();//请求列表信息
    
    void onHeroLoadedPreogress(EventCustom* msg);
    void returnFirstPoint();
    
    void onSpeedMsgProcess(EventCustom* msg);//加速跑
    void addEventListener();
    void removeEventListener();
    void onHeroLoaded();
    void onSureRunSucceed();//加速跑完成
private:
    int TAG_SHANGJAITIME;//倒计时时间
    long m_shangjiatimess;//倒计时的时间
    Label* m_shangjiatimeLabel;
    int m_idx;
    int TAG_MAP;
    int TAG_HERO;
    int m_tag;//
};


#endif /* defined(__FightPass__FindCellLayer__) */
