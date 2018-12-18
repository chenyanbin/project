#include "DictEquipHardenLevelManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipHardenLevelManager* DictEquipHardenLevelManager::_instance = NULL;
void DictEquipHardenLevelManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipHardenLevel* data = new DictEquipHardenLevel();
			
			data->id = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->levelUp = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictEquipHardenLevel* DictEquipHardenLevelManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipHardenLevel* data = (DictEquipHardenLevel*)(data_list.at(key));
	return data;
}
DictEquipHardenLevelManager* DictEquipHardenLevelManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipHardenLevelManager();
	}
	return _instance;
}
Vector<DictEquipHardenLevel*>* DictEquipHardenLevelManager::getDataList()
{
	Vector<DictEquipHardenLevel*>* list = new Vector<DictEquipHardenLevel*>();
	for(auto value : data_list)
	{
		DictEquipHardenLevel* data  = ( DictEquipHardenLevel* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipHardenLevelManager::~DictEquipHardenLevelManager()
{
	destroyInstance();
}
void DictEquipHardenLevelManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
