#include "DictLegendBattleMonsterManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendBattleMonsterManager* DictLegendBattleMonsterManager::_instance = NULL;
void DictLegendBattleMonsterManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendBattleMonster* data = new DictLegendBattleMonster();
			
			data->id = item->valueInt;
			item = item->next;			
			data->bossName = item->valueString; 
			item = item->next;			
			data->team = item->valueInt;
			item = item->next;			
			data->monsterQuality = item->valueInt;
			item = item->next;			
			data->sight = item->valueInt;
			item = item->next;			
			data->range = item->valueInt;
			item = item->next;			
			data->speed = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->aiID = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendBattleMonster* DictLegendBattleMonsterManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendBattleMonster* data = (DictLegendBattleMonster*)(data_list.at(key));
	return data;
}
DictLegendBattleMonsterManager* DictLegendBattleMonsterManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendBattleMonsterManager();
	}
	return _instance;
}
Vector<DictLegendBattleMonster*>* DictLegendBattleMonsterManager::getDataList()
{
	Vector<DictLegendBattleMonster*>* list = new Vector<DictLegendBattleMonster*>();
	for(auto value : data_list)
	{
		DictLegendBattleMonster* data  = ( DictLegendBattleMonster* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendBattleMonsterManager::~DictLegendBattleMonsterManager()
{
	destroyInstance();
}
void DictLegendBattleMonsterManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
