#include "DictTaskDayRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskDayRewardManager* DictTaskDayRewardManager::_instance = NULL;
void DictTaskDayRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskDayReward* data = new DictTaskDayReward();
			
			data->taskId = item->valueInt;
			item = item->next;			
			data->taskName = item->valueString; 
			item = item->next;			
			data->item1Type = item->valueInt;
			item = item->next;			
			data->item1Id = item->valueInt;
			item = item->next;			
			data->item1Number = item->valueInt;
			item = item->next;			
			data->item2Type = item->valueInt;
			item = item->next;			
			data->item2Id = item->valueInt;
			item = item->next;			
			data->item2Number = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->taskId), data);
		}
		node = node->next;
	}
}
DictTaskDayReward* DictTaskDayRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskDayReward* data = (DictTaskDayReward*)(data_list.at(key));
	return data;
}
DictTaskDayRewardManager* DictTaskDayRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskDayRewardManager();
	}
	return _instance;
}
Vector<DictTaskDayReward*>* DictTaskDayRewardManager::getDataList()
{
	Vector<DictTaskDayReward*>* list = new Vector<DictTaskDayReward*>();
	for(auto value : data_list)
	{
		DictTaskDayReward* data  = ( DictTaskDayReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskDayRewardManager::~DictTaskDayRewardManager()
{
	destroyInstance();
}
void DictTaskDayRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
