//
//  MusouBattleList.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/18.
//
//

#ifndef __FightPass__MusouBattleList__
#define __FightPass__MusouBattleList__

#include "../BaseLayer.h"
#include "../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
#include "../../commonData/dictData/DictMusouBattleReward/DictMusouBattleRewardManager.h"
#include "../../commonData/dictData/DictMusouBattlePrestigeReward/DictMusouBattlePrestigeRewardManager.h"
#include "MusouBattleData.h"
#include "../../common/TouchSprite/TouchSprite.h"
class MusouBattleList:public BaseLayer
{
public:
    MusouBattleList();
    ~MusouBattleList();
    virtual bool init(Vector<MusouBattleData*>* battleList);
    static MusouBattleList* create(Vector<MusouBattleData*>* battleList);
private:
    Sprite* getBattleItem(int index);
    void setBattleList();
    void onGoBtnclick(Ref* pSender);
    
    void setDropItems(Node* parent,Vector<PrizeData*>* items);//设置掉落物
    void setDropPrestigeItems(Node* parent,Vector<PrizeData*>* items);
    void onDropItemClick(Node* node);
    void onPrestigeClick(Node* node);
    TouchSprite* getItemIcon(const char* resource,int quality);
private:
    Vector<MusouBattleData*>* m_battleList;

};
#endif /* defined(__FightPass__MusouBattleList__) */
