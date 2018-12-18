#include "DictHeroPropLevelManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroPropLevelManager* DictHeroPropLevelManager::_instance = NULL;
void DictHeroPropLevelManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroPropLevel* data = new DictHeroPropLevel();
			
			data->id = item->valueInt;
			item = item->next;			
			data->heroId = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->health = item->valueInt;
			item = item->next;			
			data->attack = item->valueInt;
			item = item->next;			
			data->defend = item->valueInt;
			item = item->next;			
			data->critic = item->valueInt;
			item = item->next;			
			data->tenaci = item->valueInt;
			item = item->next;			
			data->hit = item->valueInt;
			item = item->next;			
			data->block = item->valueInt;
			item = item->next;			
			data->damageAdd = item->valueInt;
			item = item->next;			
			data->fireResist = item->valueInt;
			item = item->next;			
			data->iceResist = item->valueInt;
			item = item->next;			
			data->boltResist = item->valueInt;
			item = item->next;			
			data->windResist = item->valueInt;
			item = item->next;			
			data->poisonResist = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictHeroPropLevel* DictHeroPropLevelManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroPropLevel* data = (DictHeroPropLevel*)(data_list.at(key));
	return data;
}
DictHeroPropLevelManager* DictHeroPropLevelManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroPropLevelManager();
	}
	return _instance;
}
Vector<DictHeroPropLevel*>* DictHeroPropLevelManager::getDataList()
{
	Vector<DictHeroPropLevel*>* list = new Vector<DictHeroPropLevel*>();
	for(auto value : data_list)
	{
		DictHeroPropLevel* data  = ( DictHeroPropLevel* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroPropLevelManager::~DictHeroPropLevelManager()
{
	destroyInstance();
}
void DictHeroPropLevelManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
