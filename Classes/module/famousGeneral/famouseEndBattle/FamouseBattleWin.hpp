//
//  FamouseBattleWin.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/21.
//
//

#ifndef FamouseBattleWin_hpp
#define FamouseBattleWin_hpp
#include "../../BaseLayer.h"
#include "../../../commonData/data/DictAvatarProp.h"
class FamouseBattleWin:public BaseLayer
{
public:
    FamouseBattleWin();
    ~FamouseBattleWin();
    virtual bool init(int bossID,int hurt,int useHpBottleCount);
    static FamouseBattleWin* create(int bossID,int hurt,int useHpBottleCount);
    static void show(int bossID,int hurt,int useHpBottleCount);
private:
    void setTitle();
    void setEndBtn();
    void requestWinMsg();
    void onMsgProcess(EventCustom* message);
    void setUserInfo();
    void setHeroList();
    void onEndBtnClick(Ref* pSender);
    void onAgainClick(Ref* pSender);
    void setVSFlag();
    void setFightPower();
    void setScore();
    void setBossHead();
    void onComboClick(Ref* pSender);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    
    int m_bossID;
    int m_hurt;
    int m_useBloodBottle;//使用血瓶数量
    
    int m_score;
    int expAdd;
    int coinAdd;
    int roleLevelOld;
    int roleLevelNew;
    int bossRemainSeconds;//秒
    int lineupCombatPower;
    int lineupPrestige;//阵容声望
    int bossDictId;
    int bossLevel;
    float bossHp;
    float bossMaxHp;
    int attackCount;//	可用挑战次数	short	Y
    int attackCountMax;//	最大挑战次数	short	Y
    Vector<DictAvatarProp*>* heroList;
};

#endif /* FamouseBattleWin_hpp */
