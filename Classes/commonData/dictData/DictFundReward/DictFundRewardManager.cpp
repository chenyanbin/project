#include "DictFundRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictFundRewardManager* DictFundRewardManager::_instance = NULL;
void DictFundRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFundReward* data = new DictFundReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictFundReward* DictFundRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFundReward* data = (DictFundReward*)(data_list.at(key));
	return data;
}
DictFundRewardManager* DictFundRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFundRewardManager();
	}
	return _instance;
}
Vector<DictFundReward*>* DictFundRewardManager::getDataList()
{
	Vector<DictFundReward*>* list = new Vector<DictFundReward*>();
	for(auto value : data_list)
	{
		DictFundReward* data  = ( DictFundReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFundRewardManager::~DictFundRewardManager()
{
	destroyInstance();
}
void DictFundRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
