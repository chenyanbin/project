//
//  MusouBattle.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/12/10.
//三国无双战斗层
//

#ifndef MusouBattle_hpp
#define MusouBattle_hpp

#include "../BaseLayer.h"
#include "../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
#include "../../commonData/dictData/DictMusouBattleReward/DictMusouBattleRewardManager.h"
#include "../../commonData/dictData/DictMusouBattlePrestigeReward/DictMusouBattlePrestigeRewardManager.h"
#include "MusouBattleData.h"
#include "../../common/TouchSprite/TouchSprite.h"
class MusouBattle:public BaseLayer
{
public:
    enum
    {
        TAG_LEVEL1,
        TAG_LEVEL2,
        TAG_LEVEL3,
        TAG_LEVEL4,
        TAG_LEVEL5
    };
    MusouBattle();
    ~MusouBattle();
    virtual bool init(Vector<MusouBattleData*>* battleList);
    static MusouBattle* create(Vector<MusouBattleData*>* battleList);
private:
    void setLevelButton();
    void onButtonClick(Ref* pSender);
    void setNowSelected(int index);
    void setName(const char* name);
    void setDropItems(Vector<PrizeData*>* items);//设置掉落物
    TouchSprite* getItemIcon(const char* resource,int quality);
    void onDropItemClick(Node* pSender);
    void setInstruction(const char* content);
    void setCostPower();
    void setFightBtn();
    void onFightClick(Ref* pSender);
private:
     Vector<MusouBattleData*>* m_battleList;
    Sprite* m_curSelectedSpr;
    MusouBattleData* nowData;
private:
    int TAG_LEVELBTN;
    int TAG_NAME;
    int TAG_DROPITEMS;
    int TAG_INSTRUCTION;
    int TAG_BODYPOWER;
    int TAG_FIGHT;
};

#endif /* MusouBattle_hpp */
