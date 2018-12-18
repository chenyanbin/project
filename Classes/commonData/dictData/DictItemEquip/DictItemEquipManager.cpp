#include "DictItemEquipManager.h"
#include "../../../common/PublicShowUI.h"

DictItemEquipManager* DictItemEquipManager::_instance = NULL;
void DictItemEquipManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItemEquip* data = new DictItemEquip();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->backPackSell = item->valueInt;
			item = item->next;			
			data->sellingPrice = item->valueInt;
			item = item->next;			
			data->backPackOrder = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->parts = item->valueInt;
			item = item->next;			
			data->sellOrder = item->valueInt;
			item = item->next;			
			data->dropStageBattle = item->valueInt;
			item = item->next;			
			data->levelColour = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItemEquip* DictItemEquipManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItemEquip* data = (DictItemEquip*)(data_list.at(key));
	return data;
}
DictItemEquipManager* DictItemEquipManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemEquipManager();
	}
	return _instance;
}
Vector<DictItemEquip*>* DictItemEquipManager::getDataList()
{
	Vector<DictItemEquip*>* list = new Vector<DictItemEquip*>();
	for(auto value : data_list)
	{
		DictItemEquip* data  = ( DictItemEquip* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemEquipManager::~DictItemEquipManager()
{
	destroyInstance();
}
void DictItemEquipManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
