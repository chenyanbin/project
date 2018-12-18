//
//  BattleWin.h
//  FightPass
//
//  Created by zhangxiaobin on 15/6/23.
//
//

#ifndef __FightPass__BattleWin__
#define __FightPass__BattleWin__

#include "../../BaseLayer.h"
#include "../../../commonData/data/DictAvatarProp.h"
class PrizeData:public Ref
{
public:
    PrizeData():itemDictId(0),itemType(0),itemCount(0),conType(0),itemQuality(0)
    {};
    int itemDictId;
    int itemType;
    int itemCount;
    int conType;
    int itemQuality;
    
};

class BattleWin:public BaseLayer
{
public:
    BattleWin();
    ~BattleWin();
    virtual bool init(int battleID,float leftLife,int bloodBottle,int dropCoinAdd,long useTime);
    static BattleWin* create(int battleID,float leftLife,int bloodBottle,int dropCoinAdd,long useTime);
    static void show(int battleID,float leftLife,int bloodBottle,int dropCoinAdd,long useTime);
private:
    void setItemBg();
    void setHeroList();
    void setUserInfo();
    void setStar();
    void setTitle();
    void setEndBtn();
    void onEndBtnClick(Ref* pSender);
    void onAgainClick(Ref* pSender);
    void setPrizeItem();
    void setStarInstruction();
    void showStartEffect(float dt);//星级动画效
    void showStarSound(Node* target);
    void onItemClick(Node* node);
    void onSoundReset();
    void setTitleEffect();
    void showUserInfo();
    void startStarEffect();
    Node* getIconByTypeID(int typeId,int id,int quality);
protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    virtual void addEventListener();
    virtual void removeEventListener();
    void onMsgProcess(EventCustom* message);
protected:
    Vector<PrizeData*>* commonDrops;//普通掉落
    Vector<PrizeData*>* prestigeDrops;//声望掉落
    Vector<DictAvatarProp*>* heroList;//武将列表
    
    int TAG_ITEMBG;
    int TAG_HEADLIST;
    int TAG_USERINFO;
    int TAG_STAR;
    int TAG_EXPLABEL;
    int TAG_COINLABEL;
    
    int TAG_ENDBTN;
    int TAG_AGAINBTN;
private:
    float m_leftLife;//剩余血量
    int m_battleID;
    int m_bloodBottle;
    int expAdd;
    int coinAdd;
    int dropCoinAdd;
    int roleOldLevel;
    int roleNewLevel;
    int m_starCount;
  
    int m_starIndex;
    long m_useTime;
private:
  
};

#endif /* defined(__FightPass__BattleWin__) */
