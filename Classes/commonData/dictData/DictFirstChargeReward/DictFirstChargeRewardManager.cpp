#include "DictFirstChargeRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictFirstChargeRewardManager* DictFirstChargeRewardManager::_instance = NULL;
void DictFirstChargeRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFirstChargeReward* data = new DictFirstChargeReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->number = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictFirstChargeReward* DictFirstChargeRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFirstChargeReward* data = (DictFirstChargeReward*)(data_list.at(key));
	return data;
}
DictFirstChargeRewardManager* DictFirstChargeRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFirstChargeRewardManager();
	}
	return _instance;
}
Vector<DictFirstChargeReward*>* DictFirstChargeRewardManager::getDataList()
{
	Vector<DictFirstChargeReward*>* list = new Vector<DictFirstChargeReward*>();
	for(auto value : data_list)
	{
		DictFirstChargeReward* data  = ( DictFirstChargeReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFirstChargeRewardManager::~DictFirstChargeRewardManager()
{
	destroyInstance();
}
void DictFirstChargeRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
