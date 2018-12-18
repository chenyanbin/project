#include "DictLeadLootPoolManager.h"
#include "../../../common/PublicShowUI.h"

DictLeadLootPoolManager* DictLeadLootPoolManager::_instance = NULL;
void DictLeadLootPoolManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLeadLootPool* data = new DictLeadLootPool();
			
			data->id = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->number = item->valueInt;
			item = item->next;			
			data->weight = item->valueInt;
			item = item->next;			
			data->itemPool = item->valueInt;
			item = item->next;			
			data->randomType = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLeadLootPool* DictLeadLootPoolManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLeadLootPool* data = (DictLeadLootPool*)(data_list.at(key));
	return data;
}
DictLeadLootPoolManager* DictLeadLootPoolManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLeadLootPoolManager();
	}
	return _instance;
}
Vector<DictLeadLootPool*>* DictLeadLootPoolManager::getDataList()
{
	Vector<DictLeadLootPool*>* list = new Vector<DictLeadLootPool*>();
	for(auto value : data_list)
	{
		DictLeadLootPool* data  = ( DictLeadLootPool* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLeadLootPoolManager::~DictLeadLootPoolManager()
{
	destroyInstance();
}
void DictLeadLootPoolManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
