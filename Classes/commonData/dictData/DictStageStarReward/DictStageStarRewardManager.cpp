#include "DictStageStarRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictStageStarRewardManager* DictStageStarRewardManager::_instance = NULL;
void DictStageStarRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageStarReward* data = new DictStageStarReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->chapterId = item->valueInt;
			item = item->next;			
			data->stageId = item->valueInt;
			item = item->next;			
			data->campaignType = item->valueInt;
			item = item->next;			
			data->starNumberProgress = item->valueInt;
			item = item->next;			
			data->conId = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
			item = item->next;			
			data->conValElite = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageStarReward* DictStageStarRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageStarReward* data = (DictStageStarReward*)(data_list.at(key));
	return data;
}
DictStageStarRewardManager* DictStageStarRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageStarRewardManager();
	}
	return _instance;
}
Vector<DictStageStarReward*>* DictStageStarRewardManager::getDataList()
{
	Vector<DictStageStarReward*>* list = new Vector<DictStageStarReward*>();
	for(auto value : data_list)
	{
		DictStageStarReward* data  = ( DictStageStarReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageStarRewardManager::~DictStageStarRewardManager()
{
	destroyInstance();
}
void DictStageStarRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
