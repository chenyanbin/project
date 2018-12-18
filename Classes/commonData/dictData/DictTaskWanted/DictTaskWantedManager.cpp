#include "DictTaskWantedManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskWantedManager* DictTaskWantedManager::_instance = NULL;
void DictTaskWantedManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskWanted* data = new DictTaskWanted();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->conditionTaskId = item->valueInt;
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskWanted* DictTaskWantedManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskWanted* data = (DictTaskWanted*)(data_list.at(key));
	return data;
}
DictTaskWantedManager* DictTaskWantedManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskWantedManager();
	}
	return _instance;
}
Vector<DictTaskWanted*>* DictTaskWantedManager::getDataList()
{
	Vector<DictTaskWanted*>* list = new Vector<DictTaskWanted*>();
	for(auto value : data_list)
	{
		DictTaskWanted* data  = ( DictTaskWanted* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskWantedManager::~DictTaskWantedManager()
{
	destroyInstance();
}
void DictTaskWantedManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
