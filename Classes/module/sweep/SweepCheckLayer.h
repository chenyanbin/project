//
//  SweepCheckLayer.h
//  FightPass
//
//  Created by chenyanbin on 15/12/9.
//
//

#ifndef __FightPass__SweepCheckLayer__
#define __FightPass__SweepCheckLayer__

#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "SweepLayer.h"
#include "../../commonData/dictData/DictStageBattleReward/DictStageBattleRewardManager.h"
#include "../../commonData/dictData/DictStageBattlePrestigeReward/DictStageBattlePrestigeRewardManager.h"//声望掉落表
class SweepCheckLayer:public BaseLayer
{
public:
    enum
    {
        TAG_PT = 0,
        TAG_JY,
        TAG_JINJI,
        TAG_SAODANG
    };
    SweepCheckLayer();
    ~SweepCheckLayer();
    virtual bool init(int stageID,Vector<StageBattleData*>* battleDataList);
    static SweepCheckLayer* create(int stageID,Vector<StageBattleData*>* battleDataList);
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
protected:
    virtual void addEventListener();
    virtual void removeEventListener();
private:
    
    void setBackGround();
    void setCardLayer(int tag);
    void onComboBoxClick(Ref* pSender);
    void onFightClick(Ref* pSedner);
    void onSweepClick(Ref* pSender);
    void onSweepOneClick(Ref* pSender);
    void setRaidsCard(EventCustom* msg = NULL);//设置扫荡令
    void setDropItems(Node* parent,int stageBattleID);//设置掉落物
//    TouchSprite* getItemIcon(const char* resource,int quality);
    void onItemClick(Node* node);
    void setStartCondition(Node* parent);//设置通关条件
private:
    int m_stageID;
    int m_stageBattleID;
    Vector<StageBattleData*>* m_battleDataList;
    Vector<DictStageBattleReward*>* rewardList;//概率
    int m_chack;//关卡
    int TAG_NODE;
    int TAG_PTPIC;
    int TAG_RAIDS;
};

#endif /* defined(__FightPass__SweepCardLayer__) */
