#include "DictEquipHardenFightPropManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipHardenFightPropManager* DictEquipHardenFightPropManager::_instance = NULL;
void DictEquipHardenFightPropManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipHardenFightProp* data = new DictEquipHardenFightProp();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->limitLevel = item->valueInt;
			item = item->next;			
			data->health = item->valueInt;
			item = item->next;			
			data->healthLevelUp = item->valueInt;
			item = item->next;			
			data->attack = item->valueInt;
			item = item->next;			
			data->attackLevelUp = item->valueInt;
			item = item->next;			
			data->defend = item->valueInt;
			item = item->next;			
			data->defendLevelUp = item->valueInt;
			item = item->next;			
			data->critic = item->valueInt;
			item = item->next;			
			data->criticLevelUp = item->valueInt;
			item = item->next;			
			data->tenaci = item->valueInt;
			item = item->next;			
			data->tenaciLevelUp = item->valueInt;
			item = item->next;			
			data->hit = item->valueInt;
			item = item->next;			
			data->hitLevelUp = item->valueInt;
			item = item->next;			
			data->block = item->valueInt;
			item = item->next;			
			data->blockLevelUp = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictEquipHardenFightProp* DictEquipHardenFightPropManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipHardenFightProp* data = (DictEquipHardenFightProp*)(data_list.at(key));
	return data;
}
DictEquipHardenFightPropManager* DictEquipHardenFightPropManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipHardenFightPropManager();
	}
	return _instance;
}
Vector<DictEquipHardenFightProp*>* DictEquipHardenFightPropManager::getDataList()
{
	Vector<DictEquipHardenFightProp*>* list = new Vector<DictEquipHardenFightProp*>();
	for(auto value : data_list)
	{
		DictEquipHardenFightProp* data  = ( DictEquipHardenFightProp* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipHardenFightPropManager::~DictEquipHardenFightPropManager()
{
	destroyInstance();
}
void DictEquipHardenFightPropManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
