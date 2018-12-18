#include "DictArenaRankFirstRiseRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaRankFirstRiseRewardManager* DictArenaRankFirstRiseRewardManager::_instance = NULL;
void DictArenaRankFirstRiseRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaRankFirstRiseReward* data = new DictArenaRankFirstRiseReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->rankMax = item->valueInt;
			item = item->next;			
			data->rankMin = item->valueInt;
			item = item->next;			
			data->goldCoefficient = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaRankFirstRiseReward* DictArenaRankFirstRiseRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaRankFirstRiseReward* data = (DictArenaRankFirstRiseReward*)(data_list.at(key));
	return data;
}
DictArenaRankFirstRiseRewardManager* DictArenaRankFirstRiseRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaRankFirstRiseRewardManager();
	}
	return _instance;
}
Vector<DictArenaRankFirstRiseReward*>* DictArenaRankFirstRiseRewardManager::getDataList()
{
	Vector<DictArenaRankFirstRiseReward*>* list = new Vector<DictArenaRankFirstRiseReward*>();
	for(auto value : data_list)
	{
		DictArenaRankFirstRiseReward* data  = ( DictArenaRankFirstRiseReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaRankFirstRiseRewardManager::~DictArenaRankFirstRiseRewardManager()
{
	destroyInstance();
}
void DictArenaRankFirstRiseRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
