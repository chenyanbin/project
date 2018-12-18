#include "DictBattlePotionCostManager.h"
#include "../../../common/PublicShowUI.h"

DictBattlePotionCostManager* DictBattlePotionCostManager::_instance = NULL;
void DictBattlePotionCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBattlePotionCost* data = new DictBattlePotionCost();
			
			data->potionTimes = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->potionTimes), data);
		}
		node = node->next;
	}
}
DictBattlePotionCost* DictBattlePotionCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBattlePotionCost* data = (DictBattlePotionCost*)(data_list.at(key));
	return data;
}
DictBattlePotionCostManager* DictBattlePotionCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBattlePotionCostManager();
	}
	return _instance;
}
Vector<DictBattlePotionCost*>* DictBattlePotionCostManager::getDataList()
{
	Vector<DictBattlePotionCost*>* list = new Vector<DictBattlePotionCost*>();
	for(auto value : data_list)
	{
		DictBattlePotionCost* data  = ( DictBattlePotionCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBattlePotionCostManager::~DictBattlePotionCostManager()
{
	destroyInstance();
}
void DictBattlePotionCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
