#include "DictItemHeroManager.h"
#include "../../../common/PublicShowUI.h"

DictItemHeroManager* DictItemHeroManager::_instance = NULL;
void DictItemHeroManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItemHero* data = new DictItemHero();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->star = item->valueInt;
			item = item->next;			
			data->heroId = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->sellOrder = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItemHero* DictItemHeroManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItemHero* data = (DictItemHero*)(data_list.at(key));
	return data;
}
DictItemHeroManager* DictItemHeroManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemHeroManager();
	}
	return _instance;
}
Vector<DictItemHero*>* DictItemHeroManager::getDataList()
{
	Vector<DictItemHero*>* list = new Vector<DictItemHero*>();
	for(auto value : data_list)
	{
		DictItemHero* data  = ( DictItemHero* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemHeroManager::~DictItemHeroManager()
{
	destroyInstance();
}
void DictItemHeroManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
