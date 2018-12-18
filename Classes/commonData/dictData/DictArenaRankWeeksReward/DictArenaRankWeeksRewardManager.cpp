#include "DictArenaRankWeeksRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaRankWeeksRewardManager* DictArenaRankWeeksRewardManager::_instance = NULL;
void DictArenaRankWeeksRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaRankWeeksReward* data = new DictArenaRankWeeksReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->rankMax = item->valueInt;
			item = item->next;			
			data->rankMin = item->valueInt;
			item = item->next;			
			data->glod = item->valueInt;
			item = item->next;			
			data->glory = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaRankWeeksReward* DictArenaRankWeeksRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaRankWeeksReward* data = (DictArenaRankWeeksReward*)(data_list.at(key));
	return data;
}
DictArenaRankWeeksRewardManager* DictArenaRankWeeksRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaRankWeeksRewardManager();
	}
	return _instance;
}
Vector<DictArenaRankWeeksReward*>* DictArenaRankWeeksRewardManager::getDataList()
{
	Vector<DictArenaRankWeeksReward*>* list = new Vector<DictArenaRankWeeksReward*>();
	for(auto value : data_list)
	{
		DictArenaRankWeeksReward* data  = ( DictArenaRankWeeksReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaRankWeeksRewardManager::~DictArenaRankWeeksRewardManager()
{
	destroyInstance();
}
void DictArenaRankWeeksRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
