#include "DictTaskCommonTypeManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskCommonTypeManager* DictTaskCommonTypeManager::_instance = NULL;
void DictTaskCommonTypeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskCommonType* data = new DictTaskCommonType();
			
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
DictTaskCommonType* DictTaskCommonTypeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskCommonType* data = (DictTaskCommonType*)(data_list.at(key));
	return data;
}
DictTaskCommonTypeManager* DictTaskCommonTypeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskCommonTypeManager();
	}
	return _instance;
}
Vector<DictTaskCommonType*>* DictTaskCommonTypeManager::getDataList()
{
	Vector<DictTaskCommonType*>* list = new Vector<DictTaskCommonType*>();
	for(auto value : data_list)
	{
		DictTaskCommonType* data  = ( DictTaskCommonType* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskCommonTypeManager::~DictTaskCommonTypeManager()
{
	destroyInstance();
}
void DictTaskCommonTypeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
