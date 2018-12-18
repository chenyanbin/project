#include "DictWeekLoginRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekLoginRewardManager* DictWeekLoginRewardManager::_instance = NULL;
void DictWeekLoginRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekLoginReward* data = new DictWeekLoginReward();
			
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
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWeekLoginReward* DictWeekLoginRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekLoginReward* data = (DictWeekLoginReward*)(data_list.at(key));
	return data;
}
DictWeekLoginRewardManager* DictWeekLoginRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekLoginRewardManager();
	}
	return _instance;
}
Vector<DictWeekLoginReward*>* DictWeekLoginRewardManager::getDataList()
{
	Vector<DictWeekLoginReward*>* list = new Vector<DictWeekLoginReward*>();
	for(auto value : data_list)
	{
		DictWeekLoginReward* data  = ( DictWeekLoginReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekLoginRewardManager::~DictWeekLoginRewardManager()
{
	destroyInstance();
}
void DictWeekLoginRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
