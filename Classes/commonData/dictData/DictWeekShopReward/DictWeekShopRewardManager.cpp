#include "DictWeekShopRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekShopRewardManager* DictWeekShopRewardManager::_instance = NULL;
void DictWeekShopRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekShopReward* data = new DictWeekShopReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->day = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->itemNumber = item->valueInt;
			item = item->next;			
			data->cost = item->valueInt;
			item = item->next;			
			data->costCheap = item->valueInt;
			item = item->next;			
			data->buyNum = item->valueInt;
			item = item->next;			
			data->baseNum = item->valueInt;
			item = item->next;			
			data->startTimes = item->valueFloat;
			item = item->next;			
			data->timesCancelNum = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWeekShopReward* DictWeekShopRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekShopReward* data = (DictWeekShopReward*)(data_list.at(key));
	return data;
}
DictWeekShopRewardManager* DictWeekShopRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekShopRewardManager();
	}
	return _instance;
}
Vector<DictWeekShopReward*>* DictWeekShopRewardManager::getDataList()
{
	Vector<DictWeekShopReward*>* list = new Vector<DictWeekShopReward*>();
	for(auto value : data_list)
	{
		DictWeekShopReward* data  = ( DictWeekShopReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekShopRewardManager::~DictWeekShopRewardManager()
{
	destroyInstance();
}
void DictWeekShopRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
