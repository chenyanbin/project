//
//  MusouBattleDataList.cpp
//  FightPass
//
//  Created by zhangxiaobin on 15/9/18.
//
//

#include "MusouBattleDataList.h"
MusouBattleDataList* MusouBattleDataList::_instance = NULL;
inline bool sortMusouBattleList(const DictMusouBattle* pair1, const DictMusouBattle* pair2)
{
    return pair1->id < pair2->id;
}
MusouBattleDataList::MusouBattleDataList()
{
    musouBattleList = DictMusouBattleManager::getInstance()->getDataList();
    sort(musouBattleList->begin(), musouBattleList->end(), sortMusouBattleList);
}
MusouBattleDataList::~MusouBattleDataList()
{
    CC_SAFE_DELETE(musouBattleList);
    musouBattleList = NULL;
    _instance = NULL;
}
MusouBattleDataList* MusouBattleDataList::getInstance()
{
    if(!_instance)
    {
        _instance = new MusouBattleDataList();
    }
    return _instance;
}
void MusouBattleDataList::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
    _instance = NULL;
}
Vector<DictMusouBattle*>* MusouBattleDataList::getMusouBattleListByMusouID(int musouID)
{
    ssize_t len = musouBattleList->size();
    Vector<DictMusouBattle*>* battleList = new Vector<DictMusouBattle*>();
    for(int i = 0; i < len; i++)
    {
        if(musouBattleList->at(i)->inStageId == musouID)
        {
            battleList->pushBack(musouBattleList->at(i));
        }
    }
    return battleList;
}