//
//  LineupFightPower.h
//  FightPass
//
//  Created by chenyanbin on 15/6/26.
//
//

#ifndef __FightPass__LineupFightPower__
#define __FightPass__LineupFightPower__

#include "../BaseLayer.h"
#include <Vector>
#include "lineup_data/LineupCountData.h"
#include "../../common/TouchSprite/TouchSprite.h"
class LineupFightPower:public BaseLayer
{
public:
    LineupFightPower();
    ~LineupFightPower();
    virtual bool init(int nowPage);
    static LineupFightPower* create(int nowPage);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
private:
    void setBackGround();
    void setButton();
    void setPage();
    void onBtnclick(Node* psender);
   
    void setzengjiaBtn();
    void setRightBtn();
    void setPageNum();
    
    void requestListMsg();
    void onMsgProcess(EventCustom* msg);
    virtual void addEventListener();
    virtual void removeEventListener();
    
    void onMsgupdataLineup(EventCustom* msg);
    void requestPageMsg(int team);
    
private:
    int m_nowPage;//现在的页数
    int m_AllPage;//当前总阵容数
    int m_totalPage;//总共能创建多少个阵容
    int m_nextConsume;//创建下一个阵容需要多少钱
    int TAG_PAGE;
    bool m_isLevel;
    Vector<LineupCountData*> *lineupCount;
    bool isRight;//判断右按钮什么时候出现
    int m_allGold;
};

#endif /* defined(__FightPass__LineupFightPower__) */
