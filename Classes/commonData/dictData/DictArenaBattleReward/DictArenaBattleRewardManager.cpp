#include "DictArenaBattleRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaBattleRewardManager* DictArenaBattleRewardManager::_instance = NULL;
void DictArenaBattleRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaBattleReward* data = new DictArenaBattleReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->victoryGlory = item->valueInt;
			item = item->next;			
			data->loseGlory = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaBattleReward* DictArenaBattleRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaBattleReward* data = (DictArenaBattleReward*)(data_list.at(key));
	return data;
}
DictArenaBattleRewardManager* DictArenaBattleRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaBattleRewardManager();
	}
	return _instance;
}
Vector<DictArenaBattleReward*>* DictArenaBattleRewardManager::getDataList()
{
	Vector<DictArenaBattleReward*>* list = new Vector<DictArenaBattleReward*>();
	for(auto value : data_list)
	{
		DictArenaBattleReward* data  = ( DictArenaBattleReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaBattleRewardManager::~DictArenaBattleRewardManager()
{
	destroyInstance();
}
void DictArenaBattleRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
