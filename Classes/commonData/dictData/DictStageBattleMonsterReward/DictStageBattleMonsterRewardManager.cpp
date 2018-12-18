#include "DictStageBattleMonsterRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBattleMonsterRewardManager* DictStageBattleMonsterRewardManager::_instance = NULL;
void DictStageBattleMonsterRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBattleMonsterReward* data = new DictStageBattleMonsterReward();
			
			data->stageMonsterId = item->valueInt;
			item = item->next;			
			data->monsterName = item->valueString; 
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->minCount = item->valueInt;
			item = item->next;			
			data->maxCount = item->valueInt;
			item = item->next;			
			data->odds = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->stageMonsterId), data);
		}
		node = node->next;
	}
}
DictStageBattleMonsterReward* DictStageBattleMonsterRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBattleMonsterReward* data = (DictStageBattleMonsterReward*)(data_list.at(key));
	return data;
}
DictStageBattleMonsterRewardManager* DictStageBattleMonsterRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBattleMonsterRewardManager();
	}
	return _instance;
}
Vector<DictStageBattleMonsterReward*>* DictStageBattleMonsterRewardManager::getDataList()
{
	Vector<DictStageBattleMonsterReward*>* list = new Vector<DictStageBattleMonsterReward*>();
	for(auto value : data_list)
	{
		DictStageBattleMonsterReward* data  = ( DictStageBattleMonsterReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBattleMonsterRewardManager::~DictStageBattleMonsterRewardManager()
{
	destroyInstance();
}
void DictStageBattleMonsterRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
