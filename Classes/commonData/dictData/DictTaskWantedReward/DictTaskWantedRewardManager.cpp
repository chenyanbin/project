#include "DictTaskWantedRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskWantedRewardManager* DictTaskWantedRewardManager::_instance = NULL;
void DictTaskWantedRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskWantedReward* data = new DictTaskWantedReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->taskId = item->valueInt;
			item = item->next;			
			data->taskName = item->valueString; 
			item = item->next;			
			data->itemId = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskWantedReward* DictTaskWantedRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskWantedReward* data = (DictTaskWantedReward*)(data_list.at(key));
	return data;
}
DictTaskWantedRewardManager* DictTaskWantedRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskWantedRewardManager();
	}
	return _instance;
}
Vector<DictTaskWantedReward*>* DictTaskWantedRewardManager::getDataList()
{
	Vector<DictTaskWantedReward*>* list = new Vector<DictTaskWantedReward*>();
	for(auto value : data_list)
	{
		DictTaskWantedReward* data  = ( DictTaskWantedReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskWantedRewardManager::~DictTaskWantedRewardManager()
{
	destroyInstance();
}
void DictTaskWantedRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
