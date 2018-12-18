#include "DictMusouBattlePrestigeRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictMusouBattlePrestigeRewardManager* DictMusouBattlePrestigeRewardManager::_instance = NULL;
void DictMusouBattlePrestigeRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMusouBattlePrestigeReward* data = new DictMusouBattlePrestigeReward();
			
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
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictMusouBattlePrestigeReward* DictMusouBattlePrestigeRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMusouBattlePrestigeReward* data = (DictMusouBattlePrestigeReward*)(data_list.at(key));
	return data;
}
DictMusouBattlePrestigeRewardManager* DictMusouBattlePrestigeRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMusouBattlePrestigeRewardManager();
	}
	return _instance;
}
Vector<DictMusouBattlePrestigeReward*>* DictMusouBattlePrestigeRewardManager::getDataList()
{
	Vector<DictMusouBattlePrestigeReward*>* list = new Vector<DictMusouBattlePrestigeReward*>();
	for(auto value : data_list)
	{
		DictMusouBattlePrestigeReward* data  = ( DictMusouBattlePrestigeReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMusouBattlePrestigeRewardManager::~DictMusouBattlePrestigeRewardManager()
{
	destroyInstance();
}
void DictMusouBattlePrestigeRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
