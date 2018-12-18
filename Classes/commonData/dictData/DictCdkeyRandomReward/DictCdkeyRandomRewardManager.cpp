#include "DictCdkeyRandomRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictCdkeyRandomRewardManager* DictCdkeyRandomRewardManager::_instance = NULL;
void DictCdkeyRandomRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictCdkeyRandomReward* data = new DictCdkeyRandomReward();
			
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
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictCdkeyRandomReward* DictCdkeyRandomRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictCdkeyRandomReward* data = (DictCdkeyRandomReward*)(data_list.at(key));
	return data;
}
DictCdkeyRandomRewardManager* DictCdkeyRandomRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictCdkeyRandomRewardManager();
	}
	return _instance;
}
Vector<DictCdkeyRandomReward*>* DictCdkeyRandomRewardManager::getDataList()
{
	Vector<DictCdkeyRandomReward*>* list = new Vector<DictCdkeyRandomReward*>();
	for(auto value : data_list)
	{
		DictCdkeyRandomReward* data  = ( DictCdkeyRandomReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictCdkeyRandomRewardManager::~DictCdkeyRandomRewardManager()
{
	destroyInstance();
}
void DictCdkeyRandomRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
