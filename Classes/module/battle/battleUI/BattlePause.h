//
//  BattlePause.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/29.
//游戏暂停界面
//

#ifndef BattlePause_hpp
#define BattlePause_hpp

#include "../../BaseLayer.h"
class BattlePause:public BaseLayer
{
public:
    BattlePause();
    ~BattlePause();
    virtual bool init();
    CREATE_FUNC(BattlePause);
    static void show();
private:
    void setButton();
    void onPlayClick(Ref* pSender);
    void onBackClick(Ref* pSender);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
};

#endif /* BattlePause_hpp */
