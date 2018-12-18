#include "DictCardCostManager.h"
#include "../../../common/PublicShowUI.h"

DictCardCostManager* DictCardCostManager::_instance = NULL;
void DictCardCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictCardCost* data = new DictCardCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->price = item->valueInt;
			item = item->next;			
			data->goldThen = item->valueInt;
			item = item->next;			
			data->goldDaily = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictCardCost* DictCardCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictCardCost* data = (DictCardCost*)(data_list.at(key));
	return data;
}
DictCardCostManager* DictCardCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictCardCostManager();
	}
	return _instance;
}
Vector<DictCardCost*>* DictCardCostManager::getDataList()
{
	Vector<DictCardCost*>* list = new Vector<DictCardCost*>();
	for(auto value : data_list)
	{
		DictCardCost* data  = ( DictCardCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictCardCostManager::~DictCardCostManager()
{
	destroyInstance();
}
void DictCardCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
