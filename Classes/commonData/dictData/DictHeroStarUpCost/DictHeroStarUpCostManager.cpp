#include "DictHeroStarUpCostManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroStarUpCostManager* DictHeroStarUpCostManager::_instance = NULL;
void DictHeroStarUpCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroStarUpCost* data = new DictHeroStarUpCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->starLevel = item->valueInt;
			item = item->next;			
			data->needBook = item->valueInt;
			item = item->next;			
			data->combineNeedBook = item->valueInt;
			item = item->next;			
			data->needCoin = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictHeroStarUpCost* DictHeroStarUpCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroStarUpCost* data = (DictHeroStarUpCost*)(data_list.at(key));
	return data;
}
DictHeroStarUpCostManager* DictHeroStarUpCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroStarUpCostManager();
	}
	return _instance;
}
Vector<DictHeroStarUpCost*>* DictHeroStarUpCostManager::getDataList()
{
	Vector<DictHeroStarUpCost*>* list = new Vector<DictHeroStarUpCost*>();
	for(auto value : data_list)
	{
		DictHeroStarUpCost* data  = ( DictHeroStarUpCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroStarUpCostManager::~DictHeroStarUpCostManager()
{
	destroyInstance();
}
void DictHeroStarUpCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
