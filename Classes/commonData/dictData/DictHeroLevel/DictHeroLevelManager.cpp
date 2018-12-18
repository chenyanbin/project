#include "DictHeroLevelManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroLevelManager* DictHeroLevelManager::_instance = NULL;
void DictHeroLevelManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroLevel* data = new DictHeroLevel();
			
			data->heroLevel = item->valueInt;
			item = item->next;			
			data->heroLevelUpExp = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->heroLevel), data);
		}
		node = node->next;
	}
}
DictHeroLevel* DictHeroLevelManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroLevel* data = (DictHeroLevel*)(data_list.at(key));
	return data;
}
DictHeroLevelManager* DictHeroLevelManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroLevelManager();
	}
	return _instance;
}
Vector<DictHeroLevel*>* DictHeroLevelManager::getDataList()
{
	Vector<DictHeroLevel*>* list = new Vector<DictHeroLevel*>();
	for(auto value : data_list)
	{
		DictHeroLevel* data  = ( DictHeroLevel* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroLevelManager::~DictHeroLevelManager()
{
	destroyInstance();
}
void DictHeroLevelManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
