#include "DictHeroPrestigeUpCostManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroPrestigeUpCostManager* DictHeroPrestigeUpCostManager::_instance = NULL;
void DictHeroPrestigeUpCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroPrestigeUpCost* data = new DictHeroPrestigeUpCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->consumeCoin = item->valueInt;
			item = item->next;			
			data->rewardExp = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictHeroPrestigeUpCost* DictHeroPrestigeUpCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroPrestigeUpCost* data = (DictHeroPrestigeUpCost*)(data_list.at(key));
	return data;
}
DictHeroPrestigeUpCostManager* DictHeroPrestigeUpCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroPrestigeUpCostManager();
	}
	return _instance;
}
Vector<DictHeroPrestigeUpCost*>* DictHeroPrestigeUpCostManager::getDataList()
{
	Vector<DictHeroPrestigeUpCost*>* list = new Vector<DictHeroPrestigeUpCost*>();
	for(auto value : data_list)
	{
		DictHeroPrestigeUpCost* data  = ( DictHeroPrestigeUpCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroPrestigeUpCostManager::~DictHeroPrestigeUpCostManager()
{
	destroyInstance();
}
void DictHeroPrestigeUpCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
