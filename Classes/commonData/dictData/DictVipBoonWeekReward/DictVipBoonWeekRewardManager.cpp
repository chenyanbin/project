#include "DictVipBoonWeekRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictVipBoonWeekRewardManager* DictVipBoonWeekRewardManager::_instance = NULL;
void DictVipBoonWeekRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictVipBoonWeekReward* data = new DictVipBoonWeekReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->vipLevel = item->valueInt;
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
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictVipBoonWeekReward* DictVipBoonWeekRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictVipBoonWeekReward* data = (DictVipBoonWeekReward*)(data_list.at(key));
	return data;
}
DictVipBoonWeekRewardManager* DictVipBoonWeekRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictVipBoonWeekRewardManager();
	}
	return _instance;
}
Vector<DictVipBoonWeekReward*>* DictVipBoonWeekRewardManager::getDataList()
{
	Vector<DictVipBoonWeekReward*>* list = new Vector<DictVipBoonWeekReward*>();
	for(auto value : data_list)
	{
		DictVipBoonWeekReward* data  = ( DictVipBoonWeekReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictVipBoonWeekRewardManager::~DictVipBoonWeekRewardManager()
{
	destroyInstance();
}
void DictVipBoonWeekRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
