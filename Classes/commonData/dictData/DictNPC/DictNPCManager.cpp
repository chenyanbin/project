#include "DictNPCManager.h"
#include "../../../common/PublicShowUI.h"

DictNPCManager* DictNPCManager::_instance = NULL;
void DictNPCManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictNPC* data = new DictNPC();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->resourceHighShifting = item->valueInt;
			item = item->next;			
			data->openFunction = item->valueInt;
			item = item->next;			
			data->resourceShifting = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictNPC* DictNPCManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictNPC* data = (DictNPC*)(data_list.at(key));
	return data;
}
DictNPCManager* DictNPCManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictNPCManager();
	}
	return _instance;
}
Vector<DictNPC*>* DictNPCManager::getDataList()
{
	Vector<DictNPC*>* list = new Vector<DictNPC*>();
	for(auto value : data_list)
	{
		DictNPC* data  = ( DictNPC* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictNPCManager::~DictNPCManager()
{
	destroyInstance();
}
void DictNPCManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
