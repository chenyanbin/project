#include "DictHeroLineupKarmaManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroLineupKarmaManager* DictHeroLineupKarmaManager::_instance = NULL;
void DictHeroLineupKarmaManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroLineupKarma* data = new DictHeroLineupKarma();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->desc2 = item->valueString; 
			item = item->next;			
			data->ownHero = item->valueString; 
			item = item->next;			
			data->ownHeroId = item->valueInt;
			item = item->next;			
			data->karmaHero = item->valueString; 
			item = item->next;			
			data->karmaHeroId = item->valueInt;
			item = item->next;			
			data->fightProp = item->valueInt;
			item = item->next;			
			data->fightPropValue = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictHeroLineupKarma* DictHeroLineupKarmaManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroLineupKarma* data = (DictHeroLineupKarma*)(data_list.at(key));
	return data;
}
DictHeroLineupKarmaManager* DictHeroLineupKarmaManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroLineupKarmaManager();
	}
	return _instance;
}
Vector<DictHeroLineupKarma*>* DictHeroLineupKarmaManager::getDataList()
{
	Vector<DictHeroLineupKarma*>* list = new Vector<DictHeroLineupKarma*>();
	for(auto value : data_list)
	{
		DictHeroLineupKarma* data  = ( DictHeroLineupKarma* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroLineupKarmaManager::~DictHeroLineupKarmaManager()
{
	destroyInstance();
}
void DictHeroLineupKarmaManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
