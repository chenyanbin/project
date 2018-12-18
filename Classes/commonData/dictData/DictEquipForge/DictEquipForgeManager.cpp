#include "DictEquipForgeManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipForgeManager* DictEquipForgeManager::_instance = NULL;
void DictEquipForgeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipForge* data = new DictEquipForge();
			
			data->needEquit = item->valueInt;
			item = item->next;			
			data->needItem = item->valueInt;
			item = item->next;			
			data->needItemNumber = item->valueInt;
			item = item->next;			
			data->forgeEquip = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->needEquit), data);
		}
		node = node->next;
	}
}
DictEquipForge* DictEquipForgeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipForge* data = (DictEquipForge*)(data_list.at(key));
	return data;
}
DictEquipForgeManager* DictEquipForgeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipForgeManager();
	}
	return _instance;
}
Vector<DictEquipForge*>* DictEquipForgeManager::getDataList()
{
	Vector<DictEquipForge*>* list = new Vector<DictEquipForge*>();
	for(auto value : data_list)
	{
		DictEquipForge* data  = ( DictEquipForge* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipForgeManager::~DictEquipForgeManager()
{
	destroyInstance();
}
void DictEquipForgeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
