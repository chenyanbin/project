#include "DictMusouManager.h"
#include "../../../common/PublicShowUI.h"

DictMusouManager* DictMusouManager::_instance = NULL;
void DictMusouManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMusou* data = new DictMusou();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->inTypeEnumId = item->valueInt;
			item = item->next;			
			data->weekId1 = item->valueInt;
			item = item->next;			
			data->openTime1 = item->valueString; 
			item = item->next;			
			data->closeTime1 = item->valueString; 
			item = item->next;			
			data->weekId2 = item->valueInt;
			item = item->next;			
			data->openTime2 = item->valueString; 
			item = item->next;			
			data->closeTime2 = item->valueString; 
			item = item->next;			
			data->weekId3 = item->valueInt;
			item = item->next;			
			data->openTime3 = item->valueString; 
			item = item->next;			
			data->closeTime3 = item->valueString; 
			item = item->next;			
			data->weekId4 = item->valueInt;
			item = item->next;			
			data->openTime4 = item->valueString; 
			item = item->next;			
			data->closeTime4 = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictMusou* DictMusouManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMusou* data = (DictMusou*)(data_list.at(key));
	return data;
}
DictMusouManager* DictMusouManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMusouManager();
	}
	return _instance;
}
Vector<DictMusou*>* DictMusouManager::getDataList()
{
	Vector<DictMusou*>* list = new Vector<DictMusou*>();
	for(auto value : data_list)
	{
		DictMusou* data  = ( DictMusou* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMusouManager::~DictMusouManager()
{
	destroyInstance();
}
void DictMusouManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
