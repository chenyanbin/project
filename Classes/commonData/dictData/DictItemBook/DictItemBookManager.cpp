#include "DictItemBookManager.h"
#include "../../../common/PublicShowUI.h"

DictItemBookManager* DictItemBookManager::_instance = NULL;
void DictItemBookManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItemBook* data = new DictItemBook();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->stackNumber = item->valueInt;
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->heroId = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItemBook* DictItemBookManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItemBook* data = (DictItemBook*)(data_list.at(key));
	return data;
}
DictItemBookManager* DictItemBookManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemBookManager();
	}
	return _instance;
}
Vector<DictItemBook*>* DictItemBookManager::getDataList()
{
	Vector<DictItemBook*>* list = new Vector<DictItemBook*>();
	for(auto value : data_list)
	{
		DictItemBook* data  = ( DictItemBook* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemBookManager::~DictItemBookManager()
{
	destroyInstance();
}
void DictItemBookManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
