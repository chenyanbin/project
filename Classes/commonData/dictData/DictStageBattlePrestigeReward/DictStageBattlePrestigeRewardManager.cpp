#include "DictStageBattlePrestigeRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBattlePrestigeRewardManager* DictStageBattlePrestigeRewardManager::_instance = NULL;
void DictStageBattlePrestigeRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBattlePrestigeReward* data = new DictStageBattlePrestigeReward();
			
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
			data->itemTypeElite = item->valueInt;
			item = item->next;			
			data->itemIdElite = item->valueInt;
			item = item->next;			
			data->itemNumberElite = item->valueInt;
			item = item->next;			
			data->lootOddsBaseElite = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageBattlePrestigeReward* DictStageBattlePrestigeRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBattlePrestigeReward* data = (DictStageBattlePrestigeReward*)(data_list.at(key));
	return data;
}
DictStageBattlePrestigeRewardManager* DictStageBattlePrestigeRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBattlePrestigeRewardManager();
	}
	return _instance;
}
Vector<DictStageBattlePrestigeReward*>* DictStageBattlePrestigeRewardManager::getDataList()
{
	Vector<DictStageBattlePrestigeReward*>* list = new Vector<DictStageBattlePrestigeReward*>();
	for(auto value : data_list)
	{
		DictStageBattlePrestigeReward* data  = ( DictStageBattlePrestigeReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBattlePrestigeRewardManager::~DictStageBattlePrestigeRewardManager()
{
	destroyInstance();
}
void DictStageBattlePrestigeRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
