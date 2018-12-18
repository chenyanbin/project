#include "DictWeekCostRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekCostRewardManager* DictWeekCostRewardManager::_instance = NULL;
void DictWeekCostRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekCostReward* data = new DictWeekCostReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->day = item->valueInt;
			item = item->next;			
			data->charge = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->itemNumber = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWeekCostReward* DictWeekCostRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekCostReward* data = (DictWeekCostReward*)(data_list.at(key));
	return data;
}
DictWeekCostRewardManager* DictWeekCostRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekCostRewardManager();
	}
	return _instance;
}
Vector<DictWeekCostReward*>* DictWeekCostRewardManager::getDataList()
{
	Vector<DictWeekCostReward*>* list = new Vector<DictWeekCostReward*>();
	for(auto value : data_list)
	{
		DictWeekCostReward* data  = ( DictWeekCostReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekCostRewardManager::~DictWeekCostRewardManager()
{
	destroyInstance();
}
void DictWeekCostRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
