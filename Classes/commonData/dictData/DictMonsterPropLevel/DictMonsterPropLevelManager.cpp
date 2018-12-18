#include "DictMonsterPropLevelManager.h"
#include "../../../common/PublicShowUI.h"

DictMonsterPropLevelManager* DictMonsterPropLevelManager::_instance = NULL;
void DictMonsterPropLevelManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMonsterPropLevel* data = new DictMonsterPropLevel();
			
			data->id = item->valueInt;
			item = item->next;			
			data->monsterId = item->valueInt;
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
DictMonsterPropLevel* DictMonsterPropLevelManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMonsterPropLevel* data = (DictMonsterPropLevel*)(data_list.at(key));
	return data;
}
DictMonsterPropLevelManager* DictMonsterPropLevelManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMonsterPropLevelManager();
	}
	return _instance;
}
Vector<DictMonsterPropLevel*>* DictMonsterPropLevelManager::getDataList()
{
	Vector<DictMonsterPropLevel*>* list = new Vector<DictMonsterPropLevel*>();
	for(auto value : data_list)
	{
		DictMonsterPropLevel* data  = ( DictMonsterPropLevel* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMonsterPropLevelManager::~DictMonsterPropLevelManager()
{
	destroyInstance();
}
void DictMonsterPropLevelManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
