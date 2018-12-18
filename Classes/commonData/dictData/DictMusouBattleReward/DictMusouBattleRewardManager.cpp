#include "DictMusouBattleRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictMusouBattleRewardManager* DictMusouBattleRewardManager::_instance = NULL;
void DictMusouBattleRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMusouBattleReward* data = new DictMusouBattleReward();
			
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
DictMusouBattleReward* DictMusouBattleRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMusouBattleReward* data = (DictMusouBattleReward*)(data_list.at(key));
	return data;
}
DictMusouBattleRewardManager* DictMusouBattleRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMusouBattleRewardManager();
	}
	return _instance;
}
Vector<DictMusouBattleReward*>* DictMusouBattleRewardManager::getDataList()
{
	Vector<DictMusouBattleReward*>* list = new Vector<DictMusouBattleReward*>();
	for(auto value : data_list)
	{
		DictMusouBattleReward* data  = ( DictMusouBattleReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMusouBattleRewardManager::~DictMusouBattleRewardManager()
{
	destroyInstance();
}
void DictMusouBattleRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
