#include "DictStartHeroManager.h"
#include "../../../common/PublicShowUI.h"

DictStartHeroManager* DictStartHeroManager::_instance = NULL;
void DictStartHeroManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStartHero* data = new DictStartHero();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->itemHeroId = item->valueInt;
			item = item->next;			
			data->heroNumber = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStartHero* DictStartHeroManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStartHero* data = (DictStartHero*)(data_list.at(key));
	return data;
}
DictStartHeroManager* DictStartHeroManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStartHeroManager();
	}
	return _instance;
}
Vector<DictStartHero*>* DictStartHeroManager::getDataList()
{
	Vector<DictStartHero*>* list = new Vector<DictStartHero*>();
	for(auto value : data_list)
	{
		DictStartHero* data  = ( DictStartHero* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStartHeroManager::~DictStartHeroManager()
{
	destroyInstance();
}
void DictStartHeroManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
