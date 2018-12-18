#include "DictWeekChargeRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekChargeRewardManager* DictWeekChargeRewardManager::_instance = NULL;
void DictWeekChargeRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekChargeReward* data = new DictWeekChargeReward();
			
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
DictWeekChargeReward* DictWeekChargeRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekChargeReward* data = (DictWeekChargeReward*)(data_list.at(key));
	return data;
}
DictWeekChargeRewardManager* DictWeekChargeRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekChargeRewardManager();
	}
	return _instance;
}
Vector<DictWeekChargeReward*>* DictWeekChargeRewardManager::getDataList()
{
	Vector<DictWeekChargeReward*>* list = new Vector<DictWeekChargeReward*>();
	for(auto value : data_list)
	{
		DictWeekChargeReward* data  = ( DictWeekChargeReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekChargeRewardManager::~DictWeekChargeRewardManager()
{
	destroyInstance();
}
void DictWeekChargeRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
