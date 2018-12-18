#include "DictHeroStarManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroStarManager* DictHeroStarManager::_instance = NULL;
void DictHeroStarManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroStar* data = new DictHeroStar();
			
			data->id = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->propUpMultiple = item->valueFloat;
			item = item->next;			
			data->lootUp = item->valueInt;
			item = item->next;			
			data->toBook = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictHeroStar* DictHeroStarManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroStar* data = (DictHeroStar*)(data_list.at(key));
	return data;
}
DictHeroStarManager* DictHeroStarManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroStarManager();
	}
	return _instance;
}
Vector<DictHeroStar*>* DictHeroStarManager::getDataList()
{
	Vector<DictHeroStar*>* list = new Vector<DictHeroStar*>();
	for(auto value : data_list)
	{
		DictHeroStar* data  = ( DictHeroStar* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroStarManager::~DictHeroStarManager()
{
	destroyInstance();
}
void DictHeroStarManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
