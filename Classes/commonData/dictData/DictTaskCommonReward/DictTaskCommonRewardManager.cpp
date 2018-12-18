#include "DictTaskCommonRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskCommonRewardManager* DictTaskCommonRewardManager::_instance = NULL;
void DictTaskCommonRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskCommonReward* data = new DictTaskCommonReward();
			
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
DictTaskCommonReward* DictTaskCommonRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskCommonReward* data = (DictTaskCommonReward*)(data_list.at(key));
	return data;
}
DictTaskCommonRewardManager* DictTaskCommonRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskCommonRewardManager();
	}
	return _instance;
}
Vector<DictTaskCommonReward*>* DictTaskCommonRewardManager::getDataList()
{
	Vector<DictTaskCommonReward*>* list = new Vector<DictTaskCommonReward*>();
	for(auto value : data_list)
	{
		DictTaskCommonReward* data  = ( DictTaskCommonReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskCommonRewardManager::~DictTaskCommonRewardManager()
{
	destroyInstance();
}
void DictTaskCommonRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
