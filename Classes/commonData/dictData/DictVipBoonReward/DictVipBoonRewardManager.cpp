#include "DictVipBoonRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictVipBoonRewardManager* DictVipBoonRewardManager::_instance = NULL;
void DictVipBoonRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictVipBoonReward* data = new DictVipBoonReward();
			
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
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictVipBoonReward* DictVipBoonRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictVipBoonReward* data = (DictVipBoonReward*)(data_list.at(key));
	return data;
}
DictVipBoonRewardManager* DictVipBoonRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictVipBoonRewardManager();
	}
	return _instance;
}
Vector<DictVipBoonReward*>* DictVipBoonRewardManager::getDataList()
{
	Vector<DictVipBoonReward*>* list = new Vector<DictVipBoonReward*>();
	for(auto value : data_list)
	{
		DictVipBoonReward* data  = ( DictVipBoonReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictVipBoonRewardManager::~DictVipBoonRewardManager()
{
	destroyInstance();
}
void DictVipBoonRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
