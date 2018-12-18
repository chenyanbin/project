#include "DictHeroPropPrestigeManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroPropPrestigeManager* DictHeroPropPrestigeManager::_instance = NULL;
void DictHeroPropPrestigeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroPropPrestige* data = new DictHeroPropPrestige();
			
			data->id = item->valueInt;
			item = item->next;			
			data->heroId = item->valueInt;
			item = item->next;			
			data->prestige = item->valueInt;
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
DictHeroPropPrestige* DictHeroPropPrestigeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroPropPrestige* data = (DictHeroPropPrestige*)(data_list.at(key));
	return data;
}
DictHeroPropPrestigeManager* DictHeroPropPrestigeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroPropPrestigeManager();
	}
	return _instance;
}
Vector<DictHeroPropPrestige*>* DictHeroPropPrestigeManager::getDataList()
{
	Vector<DictHeroPropPrestige*>* list = new Vector<DictHeroPropPrestige*>();
	for(auto value : data_list)
	{
		DictHeroPropPrestige* data  = ( DictHeroPropPrestige* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroPropPrestigeManager::~DictHeroPropPrestigeManager()
{
	destroyInstance();
}
void DictHeroPropPrestigeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
