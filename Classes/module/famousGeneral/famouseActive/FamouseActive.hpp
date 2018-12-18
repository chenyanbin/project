//
//  FamouseActive.hpp
//  FightPass
// 活动页
//  Created by zhangxiaobin on 16/1/7.
//
//
#ifndef FamouseActive_hpp
#define FamouseActive_hpp
#include "../../BaseLayer.h"
#include "../../../commonData/dictData/DictLegend/DictLegendManager.h"
class FamouseActive:public BaseLayer
{
public:
    FamouseActive();
    ~FamouseActive();
    virtual bool init();
    CREATE_FUNC(FamouseActive);
private:
    void setBossBg();
    void setScoreBg();
    void requestInfo();
    void onMsgProcess(EventCustom* message);
    void setScore();
    void setBoss();
    void setGenernal();//设置武将
    void setZhaoMuButton();
    void onZhaoMuClick(Ref* pSender);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    DictLegend* dictLegend;
    int m_scoreToday;
    int m_scoreTotal;
    int m_selfRank;
private:
    int TAG_BOSSBG;
    int TAG_SCOREBG;
};

#endif /* FamouseActive_hpp */
