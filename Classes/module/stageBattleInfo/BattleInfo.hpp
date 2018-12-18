//
//  BattleInfo.hpp
//  FightPass
//
//  Created by zhangbin on 16/3/22.
//
//

#ifndef BattleInfo_hpp
#define BattleInfo_hpp

#include "../BaseLayer.h"
#include "../../common/TouchSprite/Button.h"
#include "../../common/TouchSprite/TouchSprite.h"
#include "../../commonData/dictData/DictStageBattle/DictStageBattleManager.h"
#include "StageBattleInfo.hpp"
#include "../../commonData/dictData/DictStageBattleReward/DictStageBattleRewardManager.h"
#include "../../commonData/dictData/DictStageBattlePrestigeReward/DictStageBattlePrestigeRewardManager.h"//声望掉落表
class BattleInfo:public BaseLayer
{
public:
    BattleInfo();
    ~BattleInfo();
    virtual bool init(int stageID,Vector<BattleData*>* battleDataList);
    static BattleInfo* create(int stageID,Vector<BattleData*>* battleDataList);
private:
    void setStageBattleButton();
    Node* getBattleBtn(BattleData* battleData);
    void onItemClick(Ref* pSender);
    void setStartCondition();//设置通关条件
    Sprite* getSelectedNode(bool isFlipX);
    void setDescript();
    void setStageName();
    void setBattleName();
    void setTargetTeam();
    void setPrize();
    void onIconClick(Node* pSender);
    void setButton();
    void onTenBtnClick(Ref* pSender);
    void onOneBtnClick(Ref* pSender);
    void onFightClick(Ref* pSender);
    void setCost();//设置消耗
    void setRaidsCard(EventCustom* msg = NULL);//设置扫荡令

protected:
    virtual void onEnter();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();

    virtual void addEventListener();
    virtual void removeEventListener();
private:
    int m_stageID;
    int m_stageBattleID;
    Vector<BattleData*>* m_battleDataList;
    Vector<DictStageBattleReward*>* rewardList;//概率
    
    Sprite* selectedNode;
    int m_nowSelectedIndex;
private:
    int TAG_CONDITION;
    int TAG_DESCRIPT;
    int TAG_NAME;
    int TAG_PRIZE;
    int TAG_TARGETTEAM;
    int TAG_FIGHTBTN;
    int TAG_TENBTN;
    int TAG_ONEBTN;
    int TAG_POWER;
    int TAG_RAIDS;
    int TAG_BOXBG;
};

#endif /* BattleInfo_hpp */
