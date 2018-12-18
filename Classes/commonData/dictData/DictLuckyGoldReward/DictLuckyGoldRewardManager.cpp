#include "DictLuckyGoldRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictLuckyGoldRewardManager* DictLuckyGoldRewardManager::_instance = NULL;
void DictLuckyGoldRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLuckyGoldReward* data = new DictLuckyGoldReward();
			
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
DictLuckyGoldReward* DictLuckyGoldRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLuckyGoldReward* data = (DictLuckyGoldReward*)(data_list.at(key));
	return data;
}
DictLuckyGoldRewardManager* DictLuckyGoldRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLuckyGoldRewardManager();
	}
	return _instance;
}
Vector<DictLuckyGoldReward*>* DictLuckyGoldRewardManager::getDataList()
{
	Vector<DictLuckyGoldReward*>* list = new Vector<DictLuckyGoldReward*>();
	for(auto value : data_list)
	{
		DictLuckyGoldReward* data  = ( DictLuckyGoldReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLuckyGoldRewardManager::~DictLuckyGoldRewardManager()
{
	destroyInstance();
}
void DictLuckyGoldRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
