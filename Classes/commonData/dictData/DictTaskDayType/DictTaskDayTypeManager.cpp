#include "DictTaskDayTypeManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskDayTypeManager* DictTaskDayTypeManager::_instance = NULL;
void DictTaskDayTypeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskDayType* data = new DictTaskDayType();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->tcName = item->valueString; 
			item = item->next;			
			data->progressFinishConN = item->valueInt;
			item = item->next;			
			data->function = item->valueInt;
			item = item->next;			
			data->functionType = item->valueInt;
			item = item->next;			
			data->requests = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskDayType* DictTaskDayTypeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskDayType* data = (DictTaskDayType*)(data_list.at(key));
	return data;
}
DictTaskDayTypeManager* DictTaskDayTypeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskDayTypeManager();
	}
	return _instance;
}
Vector<DictTaskDayType*>* DictTaskDayTypeManager::getDataList()
{
	Vector<DictTaskDayType*>* list = new Vector<DictTaskDayType*>();
	for(auto value : data_list)
	{
		DictTaskDayType* data  = ( DictTaskDayType* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskDayTypeManager::~DictTaskDayTypeManager()
{
	destroyInstance();
}
void DictTaskDayTypeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
