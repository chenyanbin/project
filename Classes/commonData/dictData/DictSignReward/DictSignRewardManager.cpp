#include "DictSignRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictSignRewardManager* DictSignRewardManager::_instance = NULL;
void DictSignRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictSignReward* data = new DictSignReward();
			
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
			data->isDouble = item->valueInt;
			item = item->next;			
			data->vipLevel = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictSignReward* DictSignRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictSignReward* data = (DictSignReward*)(data_list.at(key));
	return data;
}
DictSignRewardManager* DictSignRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictSignRewardManager();
	}
	return _instance;
}
Vector<DictSignReward*>* DictSignRewardManager::getDataList()
{
	Vector<DictSignReward*>* list = new Vector<DictSignReward*>();
	for(auto value : data_list)
	{
		DictSignReward* data  = ( DictSignReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictSignRewardManager::~DictSignRewardManager()
{
	destroyInstance();
}
void DictSignRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
