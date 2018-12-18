//
//  LineupHeroHeadLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/8/6.
//
//

#ifndef __FightPass__LineupHeroHeadLayer__
#define __FightPass__LineupHeroHeadLayer__

#include "../BaseLayer.h"
#include <Vector>
#include "lineup_data/LineupPageData.h"
class LineupHeroHeadLayer:public BaseLayer
{
public:
    LineupHeroHeadLayer();
    ~LineupHeroHeadLayer();
    virtual bool init(int nowPage);
    static LineupHeroHeadLayer* create(int nowPage);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    
private:
    void setBackGround();
    void setCheerHero();
    void onChangePageCallBack(EventCustom* msg);
    void onlineupNo(EventCustom* msg);//返回返回当前阵容
    void onKarmaMsg(EventCustom* msg);//返回缘分
    
    virtual void addEventListener();
    virtual void removeEventListener();

private:
    int TAG_WUJIANG;
    int TAG_YUANFEN;//缘分背景
    bool isHide;
    int m_lineupNo;
    int m_index;//英雄角标
    int TAG_NAME;//名字
    int TAG_LEVEL;//等级
    
};


#endif /* defined(__FightPass__LineupHeroHeadLayer__) */
