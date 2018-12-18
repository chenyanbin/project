#include "DictLegendBattleManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendBattleManager* DictLegendBattleManager::_instance = NULL;
void DictLegendBattleManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendBattle* data = new DictLegendBattle();
			
			data->bossId = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->mapResource = item->valueString; 
			item = item->next;			
			data->nameResource = item->valueString; 
			item = item->next;			
			data->envirEffect = item->valueString; 
			item = item->next;			
			data->skyEffect = item->valueString; 
			item = item->next;			
			data->background = item->valueString; 
			item = item->next;			
			data->LayerType = item->valueInt;
			item = item->next;			
			data->battleMusic = item->valueString; 
			item = item->next;			
			data->isPause = item->valueInt;
			item = item->next;			
			data->battleTime = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->bossId), data);
		}
		node = node->next;
	}
}
DictLegendBattle* DictLegendBattleManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendBattle* data = (DictLegendBattle*)(data_list.at(key));
	return data;
}
DictLegendBattleManager* DictLegendBattleManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendBattleManager();
	}
	return _instance;
}
Vector<DictLegendBattle*>* DictLegendBattleManager::getDataList()
{
	Vector<DictLegendBattle*>* list = new Vector<DictLegendBattle*>();
	for(auto value : data_list)
	{
		DictLegendBattle* data  = ( DictLegendBattle* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendBattleManager::~DictLegendBattleManager()
{
	destroyInstance();
}
void DictLegendBattleManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
