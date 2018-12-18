#include "DictFundCostManager.h"
#include "../../../common/PublicShowUI.h"

DictFundCostManager* DictFundCostManager::_instance = NULL;
void DictFundCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFundCost* data = new DictFundCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->vipLimit = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictFundCost* DictFundCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFundCost* data = (DictFundCost*)(data_list.at(key));
	return data;
}
DictFundCostManager* DictFundCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFundCostManager();
	}
	return _instance;
}
Vector<DictFundCost*>* DictFundCostManager::getDataList()
{
	Vector<DictFundCost*>* list = new Vector<DictFundCost*>();
	for(auto value : data_list)
	{
		DictFundCost* data  = ( DictFundCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFundCostManager::~DictFundCostManager()
{
	destroyInstance();
}
void DictFundCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
