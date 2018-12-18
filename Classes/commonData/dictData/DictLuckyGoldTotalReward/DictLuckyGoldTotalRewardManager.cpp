#include "DictLuckyGoldTotalRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictLuckyGoldTotalRewardManager* DictLuckyGoldTotalRewardManager::_instance = NULL;
void DictLuckyGoldTotalRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLuckyGoldTotalReward* data = new DictLuckyGoldTotalReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->time = item->valueInt;
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
DictLuckyGoldTotalReward* DictLuckyGoldTotalRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLuckyGoldTotalReward* data = (DictLuckyGoldTotalReward*)(data_list.at(key));
	return data;
}
DictLuckyGoldTotalRewardManager* DictLuckyGoldTotalRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLuckyGoldTotalRewardManager();
	}
	return _instance;
}
Vector<DictLuckyGoldTotalReward*>* DictLuckyGoldTotalRewardManager::getDataList()
{
	Vector<DictLuckyGoldTotalReward*>* list = new Vector<DictLuckyGoldTotalReward*>();
	for(auto value : data_list)
	{
		DictLuckyGoldTotalReward* data  = ( DictLuckyGoldTotalReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLuckyGoldTotalRewardManager::~DictLuckyGoldTotalRewardManager()
{
	destroyInstance();
}
void DictLuckyGoldTotalRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
