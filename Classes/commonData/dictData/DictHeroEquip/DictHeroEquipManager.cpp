#include "DictHeroEquipManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroEquipManager* DictHeroEquipManager::_instance = NULL;
void DictHeroEquipManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroEquip* data = new DictHeroEquip();
			
			data->heroID = item->valueInt;
			item = item->next;			
			data->heroName = item->valueString; 
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->equipSlot1EquipID = item->valueInt;
			item = item->next;			
			data->equipSlot2EquipID = item->valueInt;
			item = item->next;			
			data->equipSlot3EquipID = item->valueInt;
			item = item->next;			
			data->equipSlot4EquipID = item->valueInt;
			item = item->next;			
			data->equipSlot5EquipID = item->valueInt;
			item = item->next;			
			data->equipSlot6EquipID = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->heroID), data);
		}
		node = node->next;
	}
}
DictHeroEquip* DictHeroEquipManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroEquip* data = (DictHeroEquip*)(data_list.at(key));
	return data;
}
DictHeroEquipManager* DictHeroEquipManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroEquipManager();
	}
	return _instance;
}
Vector<DictHeroEquip*>* DictHeroEquipManager::getDataList()
{
	Vector<DictHeroEquip*>* list = new Vector<DictHeroEquip*>();
	for(auto value : data_list)
	{
		DictHeroEquip* data  = ( DictHeroEquip* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroEquipManager::~DictHeroEquipManager()
{
	destroyInstance();
}
void DictHeroEquipManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
