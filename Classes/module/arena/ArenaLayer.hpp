//
//  ArenaLayer.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/9.
//
//

#ifndef ArenaLayer_hpp
#define ArenaLayer_hpp

#include "../BaseLayer.h"
class ArenaLayer:public BaseLayer
{
public:
    enum
    {
        PAGE_ARENALIST = 500,//竞技
        PAGE_ARENATEAM,//阵容
        PAGE_ARENAORDER,//排行榜
        PAGE_ARENAEXCHANGE//兑换界面
    };
    ArenaLayer();
    ~ArenaLayer();
    virtual bool init(int showPage);
    static ArenaLayer* create(int showPage);
    static void show(int showPage);
protected:
    virtual void onExit();
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void setbackGround();
    void topLayer();
    void setRightBtn();
    void onRightBtnClick(Ref* psender);
    void setBottomInstruction();
    void setTime();
    void settopPrizeTitle();
    void setTopBtn();
    void onRecoredClick(Ref* pSender);
    void onInstructionBtnClick(Ref* pSender);
    void updateTopTimePosition();//更新顶部时间位置
    
    void requestEveryTimeMsg();//
    void onEveryTimeMsgProcess(EventCustom* msg);
private:
    int m_tagLayer;
    long leftTime;
private:
    int TAG_USERWEALTH;
    int TAG_RIGHTBTN;
    int TAG_LEFTTIME;
    int TAG_TOPPRIZE;
    int TAG_RECORDBTN;
    int TAG_INSTRUCTIONBTN;
};

#endif /* ArenaLayer_hpp */
