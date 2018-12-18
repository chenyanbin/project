#include "DictTaskWantedProgressRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskWantedProgressRewardManager* DictTaskWantedProgressRewardManager::_instance = NULL;
void DictTaskWantedProgressRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskWantedProgressReward* data = new DictTaskWantedProgressReward();
			
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
DictTaskWantedProgressReward* DictTaskWantedProgressRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskWantedProgressReward* data = (DictTaskWantedProgressReward*)(data_list.at(key));
	return data;
}
DictTaskWantedProgressRewardManager* DictTaskWantedProgressRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskWantedProgressRewardManager();
	}
	return _instance;
}
Vector<DictTaskWantedProgressReward*>* DictTaskWantedProgressRewardManager::getDataList()
{
	Vector<DictTaskWantedProgressReward*>* list = new Vector<DictTaskWantedProgressReward*>();
	for(auto value : data_list)
	{
		DictTaskWantedProgressReward* data  = ( DictTaskWantedProgressReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskWantedProgressRewardManager::~DictTaskWantedProgressRewardManager()
{
	destroyInstance();
}
void DictTaskWantedProgressRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
