#include "DictCdkeyRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictCdkeyRewardManager* DictCdkeyRewardManager::_instance = NULL;
void DictCdkeyRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictCdkeyReward* data = new DictCdkeyReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->cdkey = item->valueString; 
			item = item->next;			
			data->cdkeyName = item->valueString; 
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->number = item->valueInt;
			item = item->next;			
			data->times = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictCdkeyReward* DictCdkeyRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictCdkeyReward* data = (DictCdkeyReward*)(data_list.at(key));
	return data;
}
DictCdkeyRewardManager* DictCdkeyRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictCdkeyRewardManager();
	}
	return _instance;
}
Vector<DictCdkeyReward*>* DictCdkeyRewardManager::getDataList()
{
	Vector<DictCdkeyReward*>* list = new Vector<DictCdkeyReward*>();
	for(auto value : data_list)
	{
		DictCdkeyReward* data  = ( DictCdkeyReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictCdkeyRewardManager::~DictCdkeyRewardManager()
{
	destroyInstance();
}
void DictCdkeyRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
