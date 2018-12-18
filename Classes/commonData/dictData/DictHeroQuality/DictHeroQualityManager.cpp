#include "DictHeroQualityManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroQualityManager* DictHeroQualityManager::_instance = NULL;
void DictHeroQualityManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroQuality* data = new DictHeroQuality();
			
			data->level = item->valueInt;
			item = item->next;			
			data->nameDesp = item->valueString; 
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->ename = item->valueString; 
			item = item->next;			
			data->porpUpMultiple = item->valueFloat;
			item = item->next;			
			data->levelUpLimit = item->valueInt;
			item = item->next;			
			data->levelColour = item->valueString; 
			item = item->next;			
			data->levelColourResource = item->valueString; 
			item = item->next;			
			data->baseCost = item->valueInt;
			item = item->next;			
			data->costLevelTenUp = item->valueInt;
			item = item->next;			
			data->sellMultiple = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->level), data);
		}
		node = node->next;
	}
}
DictHeroQuality* DictHeroQualityManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroQuality* data = (DictHeroQuality*)(data_list.at(key));
	return data;
}
DictHeroQualityManager* DictHeroQualityManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroQualityManager();
	}
	return _instance;
}
Vector<DictHeroQuality*>* DictHeroQualityManager::getDataList()
{
	Vector<DictHeroQuality*>* list = new Vector<DictHeroQuality*>();
	for(auto value : data_list)
	{
		DictHeroQuality* data  = ( DictHeroQuality* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroQualityManager::~DictHeroQualityManager()
{
	destroyInstance();
}
void DictHeroQualityManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
