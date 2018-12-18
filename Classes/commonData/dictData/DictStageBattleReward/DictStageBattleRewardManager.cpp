#include "DictStageBattleRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBattleRewardManager* DictStageBattleRewardManager::_instance = NULL;
void DictStageBattleRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBattleReward* data = new DictStageBattleReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->stageBattleId = item->valueInt;
			item = item->next;			
			data->stageBattleName = item->valueString; 
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemNumber = item->valueInt;
			item = item->next;			
			data->lootOddsBase = item->valueInt;
			item = item->next;			
			data->lootOddsGrow = item->valueInt;
			item = item->next;			
			data->itemTypeElite = item->valueInt;
			item = item->next;			
			data->itemIdElite = item->valueInt;
			item = item->next;			
			data->itemNumberElite = item->valueInt;
			item = item->next;			
			data->lootOddsBaseElite = item->valueInt;
			item = item->next;			
			data->lootOddsGrowElite = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageBattleReward* DictStageBattleRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBattleReward* data = (DictStageBattleReward*)(data_list.at(key));
	return data;
}
DictStageBattleRewardManager* DictStageBattleRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBattleRewardManager();
	}
	return _instance;
}
Vector<DictStageBattleReward*>* DictStageBattleRewardManager::getDataList()
{
	Vector<DictStageBattleReward*>* list = new Vector<DictStageBattleReward*>();
	for(auto value : data_list)
	{
		DictStageBattleReward* data  = ( DictStageBattleReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBattleRewardManager::~DictStageBattleRewardManager()
{
	destroyInstance();
}
void DictStageBattleRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
