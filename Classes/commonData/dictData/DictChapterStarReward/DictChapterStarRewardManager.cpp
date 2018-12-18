#include "DictChapterStarRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictChapterStarRewardManager* DictChapterStarRewardManager::_instance = NULL;
void DictChapterStarRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictChapterStarReward* data = new DictChapterStarReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->chapterId = item->valueInt;
			item = item->next;			
			data->campaignType = item->valueInt;
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
DictChapterStarReward* DictChapterStarRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictChapterStarReward* data = (DictChapterStarReward*)(data_list.at(key));
	return data;
}
DictChapterStarRewardManager* DictChapterStarRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictChapterStarRewardManager();
	}
	return _instance;
}
Vector<DictChapterStarReward*>* DictChapterStarRewardManager::getDataList()
{
	Vector<DictChapterStarReward*>* list = new Vector<DictChapterStarReward*>();
	for(auto value : data_list)
	{
		DictChapterStarReward* data  = ( DictChapterStarReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictChapterStarRewardManager::~DictChapterStarRewardManager()
{
	destroyInstance();
}
void DictChapterStarRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
