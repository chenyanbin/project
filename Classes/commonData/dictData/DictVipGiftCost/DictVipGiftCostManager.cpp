#include "DictVipGiftCostManager.h"
#include "../../../common/PublicShowUI.h"

DictVipGiftCostManager* DictVipGiftCostManager::_instance = NULL;
void DictVipGiftCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictVipGiftCost* data = new DictVipGiftCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->day = item->valueString; 
			item = item->next;			
			data->itemId = item->valueString; 
			item = item->next;			
			data->cost = item->valueInt;
			item = item->next;			
			data->costCheap = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictVipGiftCost* DictVipGiftCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictVipGiftCost* data = (DictVipGiftCost*)(data_list.at(key));
	return data;
}
DictVipGiftCostManager* DictVipGiftCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictVipGiftCostManager();
	}
	return _instance;
}
Vector<DictVipGiftCost*>* DictVipGiftCostManager::getDataList()
{
	Vector<DictVipGiftCost*>* list = new Vector<DictVipGiftCost*>();
	for(auto value : data_list)
	{
		DictVipGiftCost* data  = ( DictVipGiftCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictVipGiftCostManager::~DictVipGiftCostManager()
{
	destroyInstance();
}
void DictVipGiftCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
