#include "DictLeadCostManager.h"
#include "../../../common/PublicShowUI.h"

DictLeadCostManager* DictLeadCostManager::_instance = NULL;
void DictLeadCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLeadCost* data = new DictLeadCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->conId = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
			item = item->next;			
			data->conValTen = item->valueInt;
			item = item->next;			
			data->freeCoolDown = item->valueInt;
			item = item->next;			
			data->freeTimesFirstDay = item->valueInt;
			item = item->next;			
			data->freeTimesLimited = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLeadCost* DictLeadCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLeadCost* data = (DictLeadCost*)(data_list.at(key));
	return data;
}
DictLeadCostManager* DictLeadCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLeadCostManager();
	}
	return _instance;
}
Vector<DictLeadCost*>* DictLeadCostManager::getDataList()
{
	Vector<DictLeadCost*>* list = new Vector<DictLeadCost*>();
	for(auto value : data_list)
	{
		DictLeadCost* data  = ( DictLeadCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLeadCostManager::~DictLeadCostManager()
{
	destroyInstance();
}
void DictLeadCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
