//
//  ArenaBattleWin.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/31.
//
//

#ifndef ArenaBattleWin_hpp
#define ArenaBattleWin_hpp

#include "BattleWin.h"
class ArenaBattleWin:public BattleWin
{
public:
    ArenaBattleWin();
    ~ArenaBattleWin();
    virtual bool initWithRoleID();
    static ArenaBattleWin* create();
    static void show();
protected:

    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    void onMsgCallBack(EventCustom* message);
private:
    void setUserInfo();
    void setHeroList();
    void setTitle();
    void setOrder();
    void showHistoryBest();
private:
    long m_roleID;
    
    const char* roleName;
    int roleLevel;
    int m_nowOrder;
    int m_honour;//荣誉
    int m_gold;
    
    int changeValue;//	名次变化具体数值	int		正数→名次上升  0→名次不变
};

#endif /* ArenaBattleWin_hpp */
