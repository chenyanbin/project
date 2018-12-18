#include "DictSignEliteRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictSignEliteRewardManager* DictSignEliteRewardManager::_instance = NULL;
void DictSignEliteRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictSignEliteReward* data = new DictSignEliteReward();
			
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
DictSignEliteReward* DictSignEliteRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictSignEliteReward* data = (DictSignEliteReward*)(data_list.at(key));
	return data;
}
DictSignEliteRewardManager* DictSignEliteRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictSignEliteRewardManager();
	}
	return _instance;
}
Vector<DictSignEliteReward*>* DictSignEliteRewardManager::getDataList()
{
	Vector<DictSignEliteReward*>* list = new Vector<DictSignEliteReward*>();
	for(auto value : data_list)
	{
		DictSignEliteReward* data  = ( DictSignEliteReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictSignEliteRewardManager::~DictSignEliteRewardManager()
{
	destroyInstance();
}
void DictSignEliteRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
