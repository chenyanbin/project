#include "DictStageBattleFKRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBattleFKRewardManager* DictStageBattleFKRewardManager::_instance = NULL;
void DictStageBattleFKRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBattleFKReward* data = new DictStageBattleFKReward();
			
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
			data->itemTypeElite = item->valueInt;
			item = item->next;			
			data->itemIdElite = item->valueInt;
			item = item->next;			
			data->itemNumberElite = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageBattleFKReward* DictStageBattleFKRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBattleFKReward* data = (DictStageBattleFKReward*)(data_list.at(key));
	return data;
}
DictStageBattleFKRewardManager* DictStageBattleFKRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBattleFKRewardManager();
	}
	return _instance;
}
Vector<DictStageBattleFKReward*>* DictStageBattleFKRewardManager::getDataList()
{
	Vector<DictStageBattleFKReward*>* list = new Vector<DictStageBattleFKReward*>();
	for(auto value : data_list)
	{
		DictStageBattleFKReward* data  = ( DictStageBattleFKReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBattleFKRewardManager::~DictStageBattleFKRewardManager()
{
	destroyInstance();
}
void DictStageBattleFKRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
