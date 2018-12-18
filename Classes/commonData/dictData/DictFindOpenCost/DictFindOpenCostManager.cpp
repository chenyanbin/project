#include "DictFindOpenCostManager.h"
#include "../../../common/PublicShowUI.h"

DictFindOpenCostManager* DictFindOpenCostManager::_instance = NULL;
void DictFindOpenCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFindOpenCost* data = new DictFindOpenCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->conId = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictFindOpenCost* DictFindOpenCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFindOpenCost* data = (DictFindOpenCost*)(data_list.at(key));
	return data;
}
DictFindOpenCostManager* DictFindOpenCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFindOpenCostManager();
	}
	return _instance;
}
Vector<DictFindOpenCost*>* DictFindOpenCostManager::getDataList()
{
	Vector<DictFindOpenCost*>* list = new Vector<DictFindOpenCost*>();
	for(auto value : data_list)
	{
		DictFindOpenCost* data  = ( DictFindOpenCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFindOpenCostManager::~DictFindOpenCostManager()
{
	destroyInstance();
}
void DictFindOpenCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
