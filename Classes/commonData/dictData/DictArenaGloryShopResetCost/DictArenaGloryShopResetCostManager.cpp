#include "DictArenaGloryShopResetCostManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaGloryShopResetCostManager* DictArenaGloryShopResetCostManager::_instance = NULL;
void DictArenaGloryShopResetCostManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaGloryShopResetCost* data = new DictArenaGloryShopResetCost();
			
			data->id = item->valueInt;
			item = item->next;			
			data->resetTimes = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaGloryShopResetCost* DictArenaGloryShopResetCostManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaGloryShopResetCost* data = (DictArenaGloryShopResetCost*)(data_list.at(key));
	return data;
}
DictArenaGloryShopResetCostManager* DictArenaGloryShopResetCostManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaGloryShopResetCostManager();
	}
	return _instance;
}
Vector<DictArenaGloryShopResetCost*>* DictArenaGloryShopResetCostManager::getDataList()
{
	Vector<DictArenaGloryShopResetCost*>* list = new Vector<DictArenaGloryShopResetCost*>();
	for(auto value : data_list)
	{
		DictArenaGloryShopResetCost* data  = ( DictArenaGloryShopResetCost* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaGloryShopResetCostManager::~DictArenaGloryShopResetCostManager()
{
	destroyInstance();
}
void DictArenaGloryShopResetCostManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
