//
//  BattleCountDown.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/12.
//战场倒计时
//

#ifndef BattleCountDown_hpp
#define BattleCountDown_hpp

#include "../../BaseLayer.h"

class BattleCountDown:public BaseLayer
{
public:
    BattleCountDown();
    ~BattleCountDown();
    static BattleCountDown* getInstance();

    void start(bool isTimeWinMode , int _leftTime);
    void stop();
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
private:
    void onDelay();
private:
    int m_leftTime;
    bool m_isTimeWinMode;
    static BattleCountDown* _instance;
    int TAG_LEFTTIME;
    int TAG_ACTION;
    int TAG_TIMEBG;
};


#endif /* BattleCountDown_hpp */
