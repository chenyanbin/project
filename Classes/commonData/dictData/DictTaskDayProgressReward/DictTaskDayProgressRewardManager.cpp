#include "DictTaskDayProgressRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskDayProgressRewardManager* DictTaskDayProgressRewardManager::_instance = NULL;
void DictTaskDayProgressRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskDayProgressReward* data = new DictTaskDayProgressReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->starNumberProgress = item->valueInt;
			item = item->next;			
			data->conId = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskDayProgressReward* DictTaskDayProgressRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskDayProgressReward* data = (DictTaskDayProgressReward*)(data_list.at(key));
	return data;
}
DictTaskDayProgressRewardManager* DictTaskDayProgressRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskDayProgressRewardManager();
	}
	return _instance;
}
Vector<DictTaskDayProgressReward*>* DictTaskDayProgressRewardManager::getDataList()
{
	Vector<DictTaskDayProgressReward*>* list = new Vector<DictTaskDayProgressReward*>();
	for(auto value : data_list)
	{
		DictTaskDayProgressReward* data  = ( DictTaskDayProgressReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskDayProgressRewardManager::~DictTaskDayProgressRewardManager()
{
	destroyInstance();
}
void DictTaskDayProgressRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
