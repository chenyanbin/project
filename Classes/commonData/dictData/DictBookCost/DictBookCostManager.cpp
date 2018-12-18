#include "DictBookCostManager.h"
#include "../../../common/PublicShowUI.h"

DictBookCostManager* DictBookCostManager::_instance = NULL;
void DictBookCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBookCost* data = new DictBookCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->conId = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictBookCost* DictBookCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBookCost* data = (DictBookCost*)(data_list.at(key));
	return data;
}
DictBookCostManager* DictBookCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBookCostManager();
	}
	return _instance;
}
Vector<DictBookCost*>* DictBookCostManager::getDataList()
{
	Vector<DictBookCost*>* list = new Vector<DictBookCost*>();
	for(auto value : data_list)
	{
		DictBookCost* data  = ( DictBookCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBookCostManager::~DictBookCostManager()
{
	destroyInstance();
}
void DictBookCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
