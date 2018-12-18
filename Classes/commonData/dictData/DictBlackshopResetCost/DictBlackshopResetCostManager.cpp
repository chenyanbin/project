#include "DictBlackshopResetCostManager.h"
#include "../../../common/PublicShowUI.h"

DictBlackshopResetCostManager* DictBlackshopResetCostManager::_instance = NULL;
void DictBlackshopResetCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBlackshopResetCost* data = new DictBlackshopResetCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->resetTimes = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
			item = item->next;			
			data->time = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictBlackshopResetCost* DictBlackshopResetCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBlackshopResetCost* data = (DictBlackshopResetCost*)(data_list.at(key));
	return data;
}
DictBlackshopResetCostManager* DictBlackshopResetCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBlackshopResetCostManager();
	}
	return _instance;
}
Vector<DictBlackshopResetCost*>* DictBlackshopResetCostManager::getDataList()
{
	Vector<DictBlackshopResetCost*>* list = new Vector<DictBlackshopResetCost*>();
	for(auto value : data_list)
	{
		DictBlackshopResetCost* data  = ( DictBlackshopResetCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBlackshopResetCostManager::~DictBlackshopResetCostManager()
{
	destroyInstance();
}
void DictBlackshopResetCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
