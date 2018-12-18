//
//  LineupCheerLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#ifndef __FightPass__LineupCheerLayer__
#define __FightPass__LineupCheerLayer__

#include "../BaseLayer.h"
#include <Vector>
#include "lineup_data/LineupPageData.h"
class LineupCheerLayer:public BaseLayer
{
public:
    LineupCheerLayer();
    ~LineupCheerLayer();
    virtual bool init(int nowPage);
    static LineupCheerLayer* create(int nowPage);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();

private:
    void setBackGround();
    void setCheerHero();
    void onClick(Node* psender);
    void onlineupNo(EventCustom* msg);//获得当前阵容页
    void onHeroList(EventCustom* msg);//获得助阵武将
    virtual void addEventListener();
    virtual void removeEventListener();
    void requestLineupSetMsg(int lineupNo,int heroType, int location, int heroId);//选择英雄
    
    void jiachengData();
    void onlingdaoli(EventCustom* msg);
private:
    Vector<LineupPageData*> *cheerList;
    int TAG_CONTAINER;
    int m_lineupNo;
    int TAG_JIACHENG;//加成背景tag
    bool isHide;//是否隐藏
    int m_leader;//总领导力
    int TAG_LABEL;
};

#endif /* defined(__FightPass__LineupCheerLayer__) */
