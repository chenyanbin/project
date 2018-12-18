#include "DictHeroPrestigeManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroPrestigeManager* DictHeroPrestigeManager::_instance = NULL;
void DictHeroPrestigeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroPrestige* data = new DictHeroPrestige();
			
			data->level = item->valueInt;
			item = item->next;			
			data->levelUpNeed = item->valueInt;
			item = item->next;			
			data->lootUp1 = item->valueInt;
			item = item->next;			
			data->lootUp2 = item->valueInt;
			item = item->next;			
			data->lootUp3 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->level), data);
		}
		node = node->next;
	}
}
DictHeroPrestige* DictHeroPrestigeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroPrestige* data = (DictHeroPrestige*)(data_list.at(key));
	return data;
}
DictHeroPrestigeManager* DictHeroPrestigeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroPrestigeManager();
	}
	return _instance;
}
Vector<DictHeroPrestige*>* DictHeroPrestigeManager::getDataList()
{
	Vector<DictHeroPrestige*>* list = new Vector<DictHeroPrestige*>();
	for(auto value : data_list)
	{
		DictHeroPrestige* data  = ( DictHeroPrestige* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroPrestigeManager::~DictHeroPrestigeManager()
{
	destroyInstance();
}
void DictHeroPrestigeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
