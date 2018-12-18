#include "DictLegendBattleTouchManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendBattleTouchManager* DictLegendBattleTouchManager::_instance = NULL;
void DictLegendBattleTouchManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendBattleTouch* data = new DictLegendBattleTouch();
			
			data->stageBattleId = item->valueInt;
			item = item->next;			
			data->monsterId = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->stageBattleId), data);
		}
		node = node->next;
	}
}
DictLegendBattleTouch* DictLegendBattleTouchManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendBattleTouch* data = (DictLegendBattleTouch*)(data_list.at(key));
	return data;
}
DictLegendBattleTouchManager* DictLegendBattleTouchManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendBattleTouchManager();
	}
	return _instance;
}
Vector<DictLegendBattleTouch*>* DictLegendBattleTouchManager::getDataList()
{
	Vector<DictLegendBattleTouch*>* list = new Vector<DictLegendBattleTouch*>();
	for(auto value : data_list)
	{
		DictLegendBattleTouch* data  = ( DictLegendBattleTouch* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendBattleTouchManager::~DictLegendBattleTouchManager()
{
	destroyInstance();
}
void DictLegendBattleTouchManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
