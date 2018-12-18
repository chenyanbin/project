#include "DictArenaRankDayRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaRankDayRewardManager* DictArenaRankDayRewardManager::_instance = NULL;
void DictArenaRankDayRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaRankDayReward* data = new DictArenaRankDayReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->rankMax = item->valueInt;
			item = item->next;			
			data->rankMin = item->valueInt;
			item = item->next;			
			data->itemId1 = item->valueInt;
			item = item->next;			
			data->type1 = item->valueInt;
			item = item->next;			
			data->number1 = item->valueInt;
			item = item->next;			
			data->itemId2 = item->valueInt;
			item = item->next;			
			data->type2 = item->valueInt;
			item = item->next;			
			data->number2 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaRankDayReward* DictArenaRankDayRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaRankDayReward* data = (DictArenaRankDayReward*)(data_list.at(key));
	return data;
}
DictArenaRankDayRewardManager* DictArenaRankDayRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaRankDayRewardManager();
	}
	return _instance;
}
Vector<DictArenaRankDayReward*>* DictArenaRankDayRewardManager::getDataList()
{
	Vector<DictArenaRankDayReward*>* list = new Vector<DictArenaRankDayReward*>();
	for(auto value : data_list)
	{
		DictArenaRankDayReward* data  = ( DictArenaRankDayReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaRankDayRewardManager::~DictArenaRankDayRewardManager()
{
	destroyInstance();
}
void DictArenaRankDayRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
