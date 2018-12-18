//
//  DictManager.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/8/3.
//
//

#include "DictManager.h"
#include "../dictData/DictHeroPropLevel/DictHeroPropLevelManager.h"
#include "../dictData/DictHeroPropPrestige/DictHeroPropPrestigeManager.h"
#include "../dictData/DictMonsterPropLevel/DictMonsterPropLevelManager.h"
#include "../dictData/DictGlobalFormula/DictGlobalFormulaManager.h"
#include "../dictData/DictStageBattleMonster/DictStageBattleMonsterManager.h"
DictAvatarProp* DictManager::getDictHeroProp(int heroID,int level,int prestige)
{
    DictAvatarProp* heroProp = new DictAvatarProp();
    heroProp->autorelease();
    Vector<DictHeroPropLevel*>* list = DictHeroPropLevelManager::getInstance()->getDataList();
    for(auto propLevel: *list)
    {
        if(propLevel->heroId == heroID && propLevel->level == level)
        {
            heroProp->level = level;
            heroProp->health =propLevel->health;
            heroProp->attack = propLevel->attack;
            heroProp->defend = propLevel->defend ;
            heroProp->critic = propLevel->critic / 100;
            heroProp->tenaci = propLevel->tenaci / 100;
            heroProp->hit = propLevel->hit/ 100;
            heroProp->block = propLevel->block / 100 ;
            heroProp->damageAdd = propLevel->damageAdd / 100;
            heroProp->fireResist = propLevel->fireResist / 100;
            heroProp->iceResist = propLevel->iceResist / 100;
            heroProp->boltResist = propLevel->boltResist / 100;
            heroProp->windResist = propLevel->windResist  / 100;
            heroProp->poisonResist = propLevel->poisonResist / 100;
            break;
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    Vector<DictHeroPropPrestige*>* list1 = DictHeroPropPrestigeManager::getInstance()->getDataList();
    for(auto propPrestige: *list1)
    {
        if(propPrestige->heroId == heroID && propPrestige->prestige == prestige)
        {
            heroProp->prestige = prestige;
            heroProp->health += propPrestige->health;
            heroProp->attack +=  propPrestige->attack;
            heroProp->defend +=  propPrestige->defend;
            heroProp->critic +=  propPrestige->critic / 100;
            heroProp->tenaci += propPrestige->tenaci / 100;
            heroProp->hit +=  propPrestige->hit / 100;
            heroProp->block +=  propPrestige->block  / 100;
            heroProp->damageAdd +=  propPrestige->damageAdd / 100;
            heroProp->fireResist +=  propPrestige->fireResist / 100;
            heroProp->iceResist +=  propPrestige->iceResist / 100;
            heroProp->boltResist +=  propPrestige->boltResist / 100;
            heroProp->windResist +=  propPrestige->windResist / 100 ;
            heroProp->poisonResist +=  propPrestige->poisonResist / 100;
            break;
        }
    }
    CC_SAFE_DELETE(list1);
    list1 = NULL;

    return heroProp;
}
DictAvatarProp* DictManager::getDictMonsterProp(int monserID,int level)
{
    DictAvatarProp* mosnterProp = new DictAvatarProp();
    mosnterProp->autorelease();
    Vector<DictMonsterPropLevel*>* list = DictMonsterPropLevelManager::getInstance()->getDataList();
    for(auto propLevel: *list)
    {
        if(propLevel->monsterId == monserID && propLevel->level == level)
        {
           
            mosnterProp->level = level;
            mosnterProp->health =propLevel->health;
            mosnterProp->attack = propLevel->attack;
            mosnterProp->defend = propLevel->defend;
            mosnterProp->critic = propLevel->critic;
            mosnterProp->tenaci = propLevel->tenaci;
            mosnterProp->hit = propLevel->hit;
            mosnterProp->block = propLevel->block ;
            mosnterProp->damageAdd = propLevel->damageAdd;
            mosnterProp->fireResist = propLevel->fireResist;
            mosnterProp->iceResist = propLevel->iceResist;
            mosnterProp->boltResist = propLevel->boltResist;
            mosnterProp->windResist = propLevel->windResist ;
            mosnterProp->poisonResist = propLevel->poisonResist;
            break;
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return mosnterProp;
}
DictAvatarProp* DictManager::getStageBattleMonsterProp(int stageBattleMonsterID,bool isElite)
{//得到关卡怪的怪物属性
    DictAvatarProp* mosnterProp = new DictAvatarProp();
    mosnterProp->autorelease();
    
    DictStageBattleMonster* monster = DictStageBattleMonsterManager::getInstance()->getData(stageBattleMonsterID);
    if(!monster)
    {
        return mosnterProp;
    }
    
    mosnterProp->level = monster->monsterLevel;
    mosnterProp->health = isElite ? monster->healthE : monster->health;
    mosnterProp->attack = isElite ?monster->attackE : monster->attack;
    mosnterProp->defend = isElite ? monster->defendE : monster->defend;
    mosnterProp->critic = isElite ? monster->criticE : monster->critic;
    mosnterProp->tenaci = isElite ? monster->tenaciE : monster->tenaci;
    mosnterProp->hit =  isElite ? monster->hitE : monster->hit;
    mosnterProp->block = isElite ?monster->blockE : monster->block ;
    mosnterProp->damageAdd = isElite ?monster->damageAddE : monster->damageAdd;
    mosnterProp->fireResist = isElite ? monster->fireResistE : monster->fireResist;
    mosnterProp->iceResist = isElite ? monster->iceResistE : monster->iceResist;
    mosnterProp->boltResist = isElite ? monster->boltResistE : monster->boltResist;
    mosnterProp->windResist = isElite ? monster->windResistE : monster->windResist ;
    mosnterProp->poisonResist = isElite ? monster->poisonResistE : monster->poisonResist;
    
    return mosnterProp;
}
double DictManager::getFormulaValue(const char* formulaName)
{
    Vector<DictGlobalFormula*>* list = DictGlobalFormulaManager::getInstance()->getDataList();
    for(auto data: *list)
    {
        if(data->name == formulaName)
        {
            return atof(data->value.c_str());
        }
    }
    CC_SAFE_DELETE(list);
    list = NULL;
    return 0;
}