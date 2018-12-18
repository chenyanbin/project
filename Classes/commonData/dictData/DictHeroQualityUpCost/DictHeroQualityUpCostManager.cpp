#include "DictHeroQualityUpCostManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroQualityUpCostManager* DictHeroQualityUpCostManager::_instance = NULL;
void DictHeroQualityUpCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroQualityUpCost* data = new DictHeroQualityUpCost();
			
			data->quality = item->valueInt;
			item = item->next;			
			data->qualityDesc = item->valueString; 
			item = item->next;			
			data->coin = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->quality), data);
		}
		node = node->next;
	}
}
DictHeroQualityUpCost* DictHeroQualityUpCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroQualityUpCost* data = (DictHeroQualityUpCost*)(data_list.at(key));
	return data;
}
DictHeroQualityUpCostManager* DictHeroQualityUpCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroQualityUpCostManager();
	}
	return _instance;
}
Vector<DictHeroQualityUpCost*>* DictHeroQualityUpCostManager::getDataList()
{
	Vector<DictHeroQualityUpCost*>* list = new Vector<DictHeroQualityUpCost*>();
	for(auto value : data_list)
	{
		DictHeroQualityUpCost* data  = ( DictHeroQualityUpCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroQualityUpCostManager::~DictHeroQualityUpCostManager()
{
	destroyInstance();
}
void DictHeroQualityUpCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
