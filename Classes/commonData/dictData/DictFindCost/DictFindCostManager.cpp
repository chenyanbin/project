#include "DictFindCostManager.h"
#include "../../../common/PublicShowUI.h"

DictFindCostManager* DictFindCostManager::_instance = NULL;
void DictFindCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFindCost* data = new DictFindCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
			item = item->next;			
			data->findTime = item->valueInt;
			item = item->next;			
			data->findFastCostGold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictFindCost* DictFindCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFindCost* data = (DictFindCost*)(data_list.at(key));
	return data;
}
DictFindCostManager* DictFindCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFindCostManager();
	}
	return _instance;
}
Vector<DictFindCost*>* DictFindCostManager::getDataList()
{
	Vector<DictFindCost*>* list = new Vector<DictFindCost*>();
	for(auto value : data_list)
	{
		DictFindCost* data  = ( DictFindCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFindCostManager::~DictFindCostManager()
{
	destroyInstance();
}
void DictFindCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
