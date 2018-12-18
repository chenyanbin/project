#include "DictLineupOpenCostManager.h"
#include "../../../common/PublicShowUI.h"

DictLineupOpenCostManager* DictLineupOpenCostManager::_instance = NULL;
void DictLineupOpenCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLineupOpenCost* data = new DictLineupOpenCost();
			
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
DictLineupOpenCost* DictLineupOpenCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLineupOpenCost* data = (DictLineupOpenCost*)(data_list.at(key));
	return data;
}
DictLineupOpenCostManager* DictLineupOpenCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLineupOpenCostManager();
	}
	return _instance;
}
Vector<DictLineupOpenCost*>* DictLineupOpenCostManager::getDataList()
{
	Vector<DictLineupOpenCost*>* list = new Vector<DictLineupOpenCost*>();
	for(auto value : data_list)
	{
		DictLineupOpenCost* data  = ( DictLineupOpenCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLineupOpenCostManager::~DictLineupOpenCostManager()
{
	destroyInstance();
}
void DictLineupOpenCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
