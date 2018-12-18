#include "DictEquipForgeCostManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipForgeCostManager* DictEquipForgeCostManager::_instance = NULL;
void DictEquipForgeCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipForgeCost* data = new DictEquipForgeCost();
			
			data->quality = item->valueInt;
			item = item->next;			
			data->consumeCoin = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->quality), data);
		}
		node = node->next;
	}
}
DictEquipForgeCost* DictEquipForgeCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipForgeCost* data = (DictEquipForgeCost*)(data_list.at(key));
	return data;
}
DictEquipForgeCostManager* DictEquipForgeCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipForgeCostManager();
	}
	return _instance;
}
Vector<DictEquipForgeCost*>* DictEquipForgeCostManager::getDataList()
{
	Vector<DictEquipForgeCost*>* list = new Vector<DictEquipForgeCost*>();
	for(auto value : data_list)
	{
		DictEquipForgeCost* data  = ( DictEquipForgeCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipForgeCostManager::~DictEquipForgeCostManager()
{
	destroyInstance();
}
void DictEquipForgeCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
