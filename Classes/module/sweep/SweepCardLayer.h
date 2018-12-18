//
//  SweepCardLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/7/1.
//
//

#ifndef __FightPass__SweepCardLayer__
#define __FightPass__SweepCardLayer__

#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "SweepLayer.h"
#include "../../commonData/dictData/DictStageBattleReward/DictStageBattleRewardManager.h"
#include "../../commonData/dictData/DictStageBattlePrestigeReward/DictStageBattlePrestigeRewardManager.h"//声望掉落表
class SweepCardLayer:public BaseLayer
{
public:
    enum
    {
        TAG_PT = 0,
        TAG_JY,
        TAG_JINJI,
        TAG_SAODANG
    };
    SweepCardLayer();
    ~SweepCardLayer();
    virtual bool init(int stageID,Vector<StageBattleData*>* battleDataList);
    static SweepCardLayer* create(int stageID,Vector<StageBattleData*>* battleDataList);
    virtual void onEnter();
    virtual void onExit();
    
private:
   
    void setBackGround();
    void setCardLayer();
    void setDropItems(Node* parent,int stageBattleID);//设置掉落物
    void onFightClick(Ref* psender);
    void onSweepClick(Ref* pSender);
    TouchSprite* getItemIcon(const char* resource,int quality);
  
    
    void setDropPrestigeItems(Node* parent,int stageBattleID);
    void onItemClick(Node* node);
    void onDropPrestigeClick(Node* node);
    void onSweepOneClick(Ref* pSender);//扫荡一次
private:
    int m_stageID;

    Vector<Button*> cardList;
    Vector<StageBattleData*>* m_battleDataList;
    Vector<DictStageBattleReward*>* rewardList;//概率
    Vector<DictStageBattlePrestigeReward*>* prestigeList;//声望
};

#endif /* defined(__FightPass__SweepCardLayer__) */
