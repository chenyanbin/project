#include "DictChargeCostManager.h"
#include "../../../common/PublicShowUI.h"

DictChargeCostManager* DictChargeCostManager::_instance = NULL;
void DictChargeCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictChargeCost* data = new DictChargeCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->price = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
			item = item->next;			
			data->goldFirst = item->valueInt;
			item = item->next;			
			data->vipExpFirst = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictChargeCost* DictChargeCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictChargeCost* data = (DictChargeCost*)(data_list.at(key));
	return data;
}
DictChargeCostManager* DictChargeCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictChargeCostManager();
	}
	return _instance;
}
Vector<DictChargeCost*>* DictChargeCostManager::getDataList()
{
	Vector<DictChargeCost*>* list = new Vector<DictChargeCost*>();
	for(auto value : data_list)
	{
		DictChargeCost* data  = ( DictChargeCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictChargeCostManager::~DictChargeCostManager()
{
	destroyInstance();
}
void DictChargeCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
