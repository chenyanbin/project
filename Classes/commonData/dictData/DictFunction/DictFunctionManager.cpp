#include "DictFunctionManager.h"
#include "../../../common/PublicShowUI.h"

DictFunctionManager* DictFunctionManager::_instance = NULL;
void DictFunctionManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFunction* data = new DictFunction();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->ename = item->valueString; 
			item = item->next;			
			data->roleLevel = item->valueInt;
			item = item->next;			
			data->battleId = item->valueInt;
			item = item->next;			
			data->openingtext = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictFunction* DictFunctionManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFunction* data = (DictFunction*)(data_list.at(key));
	return data;
}
DictFunctionManager* DictFunctionManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFunctionManager();
	}
	return _instance;
}
Vector<DictFunction*>* DictFunctionManager::getDataList()
{
	Vector<DictFunction*>* list = new Vector<DictFunction*>();
	for(auto value : data_list)
	{
		DictFunction* data  = ( DictFunction* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFunctionManager::~DictFunctionManager()
{
	destroyInstance();
}
void DictFunctionManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
