//
//  MailAllGiftData.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#ifndef FightPass_MailAllGiftData_h
#define FightPass_MailAllGiftData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MailAllGiftData:public Ref
{
public:
    MailAllGiftData()
    :itemType(0)
    ,heroId(0)
    ,heroDictId(0)
    ,force(0)
    ,heroName("")
    ,heroQuality(0)
    ,heroLevel(0)
    ,prestige(0)
    ,combatPower(0)
    ,leadership(0)
    ,itemDictId(0)
    ,itemName("")
    ,itemQuality(0)
    ,itemDesc("")
    ,rolePropId(0)
    ,rolePropCount(0)
    {
        
    }
    ~MailAllGiftData()
    {
        
    }
    int itemType;//物品类型
    int heroId ;//物品ID
    int heroDictId;//物品数量
    int force;
    string heroName;
    int heroQuality;
    int heroLevel;
    int prestige;
    int combatPower;
    int leadership;
    int itemDictId;
    string itemName;
    int itemQuality;
    string itemDesc;
    int rolePropId;
    int rolePropCount;
};


#endif
