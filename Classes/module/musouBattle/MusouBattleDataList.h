//
//  MusouBattleDataList.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/18.
//
//

#ifndef __FightPass__MusouBattleDataList__
#define __FightPass__MusouBattleDataList__

#include "cocos2d.h"
USING_NS_CC;
#include "../../commonData/dictData/DictMusouBattle/DictMusouBattleManager.h"
class MusouBattleDataList
{
public:
    MusouBattleDataList();
    ~MusouBattleDataList();
    static MusouBattleDataList* getInstance();
    static void destoryInstance();
    Vector<DictMusouBattle*>* getMusouBattleListByMusouID(int musouID);
private:
    static MusouBattleDataList* _instance;
    Vector<DictMusouBattle*>* musouBattleList;
};

#endif /* defined(__FightPass__MusouBattleDataList__) */
