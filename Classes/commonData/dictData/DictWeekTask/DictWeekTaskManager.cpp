#include "DictWeekTaskManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekTaskManager* DictWeekTaskManager::_instance = NULL;
void DictWeekTaskManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekTask* data = new DictWeekTask();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->days = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->taskType = item->valueInt;
			item = item->next;			
			data->finishCon1 = item->valueString; 
			item = item->next;			
			data->finishCon2 = item->valueString; 
			item = item->next;			
			data->finishCon3 = item->valueString; 
			item = item->next;			
			data->tag = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWeekTask* DictWeekTaskManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekTask* data = (DictWeekTask*)(data_list.at(key));
	return data;
}
DictWeekTaskManager* DictWeekTaskManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekTaskManager();
	}
	return _instance;
}
Vector<DictWeekTask*>* DictWeekTaskManager::getDataList()
{
	Vector<DictWeekTask*>* list = new Vector<DictWeekTask*>();
	for(auto value : data_list)
	{
		DictWeekTask* data  = ( DictWeekTask* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekTaskManager::~DictWeekTaskManager()
{
	destroyInstance();
}
void DictWeekTaskManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
