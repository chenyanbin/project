#include "DictFundPublicRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictFundPublicRewardManager* DictFundPublicRewardManager::_instance = NULL;
void DictFundPublicRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFundPublicReward* data = new DictFundPublicReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->buyNumber = item->valueInt;
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
DictFundPublicReward* DictFundPublicRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFundPublicReward* data = (DictFundPublicReward*)(data_list.at(key));
	return data;
}
DictFundPublicRewardManager* DictFundPublicRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFundPublicRewardManager();
	}
	return _instance;
}
Vector<DictFundPublicReward*>* DictFundPublicRewardManager::getDataList()
{
	Vector<DictFundPublicReward*>* list = new Vector<DictFundPublicReward*>();
	for(auto value : data_list)
	{
		DictFundPublicReward* data  = ( DictFundPublicReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFundPublicRewardManager::~DictFundPublicRewardManager()
{
	destroyInstance();
}
void DictFundPublicRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
