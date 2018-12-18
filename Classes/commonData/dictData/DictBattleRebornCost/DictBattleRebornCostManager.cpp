#include "DictBattleRebornCostManager.h"
#include "../../../common/PublicShowUI.h"

DictBattleRebornCostManager* DictBattleRebornCostManager::_instance = NULL;
void DictBattleRebornCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBattleRebornCost* data = new DictBattleRebornCost();
			
			data->rebornTimes = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->rebornTimes), data);
		}
		node = node->next;
	}
}
DictBattleRebornCost* DictBattleRebornCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBattleRebornCost* data = (DictBattleRebornCost*)(data_list.at(key));
	return data;
}
DictBattleRebornCostManager* DictBattleRebornCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBattleRebornCostManager();
	}
	return _instance;
}
Vector<DictBattleRebornCost*>* DictBattleRebornCostManager::getDataList()
{
	Vector<DictBattleRebornCost*>* list = new Vector<DictBattleRebornCost*>();
	for(auto value : data_list)
	{
		DictBattleRebornCost* data  = ( DictBattleRebornCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBattleRebornCostManager::~DictBattleRebornCostManager()
{
	destroyInstance();
}
void DictBattleRebornCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
