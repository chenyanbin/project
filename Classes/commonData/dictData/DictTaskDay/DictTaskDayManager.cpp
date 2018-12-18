#include "DictTaskDayManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskDayManager* DictTaskDayManager::_instance = NULL;
void DictTaskDayManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskDay* data = new DictTaskDay();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->category = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->bonusExp = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->progress = item->valueInt;
			item = item->next;			
			data->taskType = item->valueInt;
			item = item->next;			
			data->finishCon1 = item->valueString; 
			item = item->next;			
			data->finishCon2 = item->valueString; 
			item = item->next;			
			data->finishCon3 = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskDay* DictTaskDayManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskDay* data = (DictTaskDay*)(data_list.at(key));
	return data;
}
DictTaskDayManager* DictTaskDayManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskDayManager();
	}
	return _instance;
}
Vector<DictTaskDay*>* DictTaskDayManager::getDataList()
{
	Vector<DictTaskDay*>* list = new Vector<DictTaskDay*>();
	for(auto value : data_list)
	{
		DictTaskDay* data  = ( DictTaskDay* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskDayManager::~DictTaskDayManager()
{
	destroyInstance();
}
void DictTaskDayManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
