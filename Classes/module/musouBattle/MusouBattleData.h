//
//  MusouBattleData.h
//  FightPass
//
//  Created by zhangxiaobin on 15/10/13.
//
//

#ifndef MusouBattleData_h
#define MusouBattleData_h
#include "../battle/settleLayer/BattleWin.h"
class MusouBattleData:public Ref
{
public:
    MusouBattleData():battleId(0),battleType(0),status(0),costPower(0)
    {
        this->rewardList = new Vector<PrizeData*>();
        this->prestigeList = new Vector<PrizeData*>();
    }
    ~MusouBattleData()
    {
        delete rewardList;
        rewardList = NULL;
        delete prestigeList;
        prestigeList = NULL;
    }
    enum
    {
        STATUS_ABLE_FIGHT = 1,//可进
        STATUS_ENABLE_FIGHT = 2//不可进
    };
public:
    int battleId;
    int battleType	;//类型	DictMusouTypeEnum
    int status;//	状态	byte	Y	1可进    2 不可进
    int costPower;//	消耗体力	int	Y
    Vector<PrizeData*>* rewardList;//普通掉落
    Vector<PrizeData*>* prestigeList;//声望掉落
};
#endif /* MusouBattleData_h */
