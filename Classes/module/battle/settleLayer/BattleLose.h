//
//  BattleLose.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/23.
//
//

#ifndef __FightPass__BattleLose__
#define __FightPass__BattleLose__

#include "../../BaseLayer.h"
class BattleLose:public BaseLayer
{
public:
    BattleLose();
    ~BattleLose();
    virtual bool init(int battleID,int m_bloodBottle);
    static BattleLose* create(int battleID,int bloodBottle);
    static void show(int battleID,int bloodBottle);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    void setTitle();
    void setButtons();
    void onAgainClick(Ref* pSender);
    void onEndBtnCick(Ref* pSender);
    void onClick(Node* pSender);
private:
    int m_battleID;
    int m_bloodBottle;
};

#endif /* defined(__FightPass__BattleLose__) */
 