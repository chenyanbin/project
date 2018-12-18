#include "DictWeekTaskRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekTaskRewardManager* DictWeekTaskRewardManager::_instance = NULL;
void DictWeekTaskRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekTaskReward* data = new DictWeekTaskReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->weekTaskId = item->valueInt;
			item = item->next;			
			data->taskName = item->valueString; 
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->itemNumber = item->valueInt;
			item = item->next;			
			data->days = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWeekTaskReward* DictWeekTaskRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekTaskReward* data = (DictWeekTaskReward*)(data_list.at(key));
	return data;
}
DictWeekTaskRewardManager* DictWeekTaskRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekTaskRewardManager();
	}
	return _instance;
}
Vector<DictWeekTaskReward*>* DictWeekTaskRewardManager::getDataList()
{
	Vector<DictWeekTaskReward*>* list = new Vector<DictWeekTaskReward*>();
	for(auto value : data_list)
	{
		DictWeekTaskReward* data  = ( DictWeekTaskReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekTaskRewardManager::~DictWeekTaskRewardManager()
{
	destroyInstance();
}
void DictWeekTaskRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
