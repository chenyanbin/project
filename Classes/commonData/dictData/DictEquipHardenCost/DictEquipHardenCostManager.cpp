#include "DictEquipHardenCostManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipHardenCostManager* DictEquipHardenCostManager::_instance = NULL;
void DictEquipHardenCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipHardenCost* data = new DictEquipHardenCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->roleLevel = item->valueInt;
			item = item->next;			
			data->equipHardenLevel = item->valueInt;
			item = item->next;			
			data->quality1Cost = item->valueInt;
			item = item->next;			
			data->quality2Cost = item->valueInt;
			item = item->next;			
			data->quality3Cost = item->valueInt;
			item = item->next;			
			data->quality4Cost = item->valueInt;
			item = item->next;			
			data->quality5Cost = item->valueInt;
			item = item->next;			
			data->quality6Cost = item->valueInt;
			item = item->next;			
			data->quality7Cost = item->valueInt;
			item = item->next;			
			data->quality8Cost = item->valueInt;
			item = item->next;			
			data->quality9Cost = item->valueInt;
			item = item->next;			
			data->quality10Cost = item->valueInt;
			item = item->next;			
			data->quality11Cost = item->valueInt;
			item = item->next;			
			data->quality12Cost = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictEquipHardenCost* DictEquipHardenCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipHardenCost* data = (DictEquipHardenCost*)(data_list.at(key));
	return data;
}
DictEquipHardenCostManager* DictEquipHardenCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipHardenCostManager();
	}
	return _instance;
}
Vector<DictEquipHardenCost*>* DictEquipHardenCostManager::getDataList()
{
	Vector<DictEquipHardenCost*>* list = new Vector<DictEquipHardenCost*>();
	for(auto value : data_list)
	{
		DictEquipHardenCost* data  = ( DictEquipHardenCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipHardenCostManager::~DictEquipHardenCostManager()
{
	destroyInstance();
}
void DictEquipHardenCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
