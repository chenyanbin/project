#include "DictLeadLootSlotsManager.h"
#include "../../../common/PublicShowUI.h"

DictLeadLootSlotsManager* DictLeadLootSlotsManager::_instance = NULL;
void DictLeadLootSlotsManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLeadLootSlots* data = new DictLeadLootSlots();
			
			data->id = item->valueInt;
			item = item->next;			
			data->drawType = item->valueInt;
			item = item->next;			
			data->slot = item->valueString; 
			item = item->next;			
			data->consumeLv = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLeadLootSlots* DictLeadLootSlotsManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLeadLootSlots* data = (DictLeadLootSlots*)(data_list.at(key));
	return data;
}
DictLeadLootSlotsManager* DictLeadLootSlotsManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLeadLootSlotsManager();
	}
	return _instance;
}
Vector<DictLeadLootSlots*>* DictLeadLootSlotsManager::getDataList()
{
	Vector<DictLeadLootSlots*>* list = new Vector<DictLeadLootSlots*>();
	for(auto value : data_list)
	{
		DictLeadLootSlots* data  = ( DictLeadLootSlots* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLeadLootSlotsManager::~DictLeadLootSlotsManager()
{
	destroyInstance();
}
void DictLeadLootSlotsManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
