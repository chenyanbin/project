#include "DictResourceManager.h"
#include "../../../common/PublicShowUI.h"

DictResourceManager* DictResourceManager::_instance = NULL;
void DictResourceManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictResource* data = new DictResource();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->propType = item->valueInt;
			item = item->next;			
			data->number = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictResource* DictResourceManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictResource* data = (DictResource*)(data_list.at(key));
	return data;
}
DictResourceManager* DictResourceManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictResourceManager();
	}
	return _instance;
}
Vector<DictResource*>* DictResourceManager::getDataList()
{
	Vector<DictResource*>* list = new Vector<DictResource*>();
	for(auto value : data_list)
	{
		DictResource* data  = ( DictResource* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictResourceManager::~DictResourceManager()
{
	destroyInstance();
}
void DictResourceManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
