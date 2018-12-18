//
//  DictManager.h
//  FightPass
//
//  Created by zhangxiaobin on 15/8/3.
//
//

#ifndef __FightPass__DictManager__
#define __FightPass__DictManager__

#include "cocos2d.h"
USING_NS_CC;
#include "DictAvatarProp.h"

class DictManager
{
public:
    static DictAvatarProp* getDictHeroProp(int heroID,int level,int prestige);
    static DictAvatarProp* getDictMonsterProp(int monserID,int level);
    static DictAvatarProp* getStageBattleMonsterProp(int stageBattleMonsterID,bool isElite);
    static double getFormulaValue(const char* formulaName);
};

#endif /* defined(__FightPass__DictManager__) */
