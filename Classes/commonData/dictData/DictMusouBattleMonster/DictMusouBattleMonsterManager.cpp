#include "DictMusouBattleMonsterManager.h"
#include "../../../common/PublicShowUI.h"

DictMusouBattleMonsterManager* DictMusouBattleMonsterManager::_instance = NULL;
void DictMusouBattleMonsterManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMusouBattleMonster* data = new DictMusouBattleMonster();
			
			data->id = item->valueInt;
			item = item->next;			
			data->monsterId = item->valueInt;
			item = item->next;			
			data->monsterName = item->valueString; 
			item = item->next;			
			data->stageBattleId = item->valueInt;
			item = item->next;			
			data->monsterLevel = item->valueInt;
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
			data->amplificationFactor = item->valueInt;
			item = item->next;			
			data->aiID = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictMusouBattleMonster* DictMusouBattleMonsterManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMusouBattleMonster* data = (DictMusouBattleMonster*)(data_list.at(key));
	return data;
}
DictMusouBattleMonsterManager* DictMusouBattleMonsterManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMusouBattleMonsterManager();
	}
	return _instance;
}
Vector<DictMusouBattleMonster*>* DictMusouBattleMonsterManager::getDataList()
{
	Vector<DictMusouBattleMonster*>* list = new Vector<DictMusouBattleMonster*>();
	for(auto value : data_list)
	{
		DictMusouBattleMonster* data  = ( DictMusouBattleMonster* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMusouBattleMonsterManager::~DictMusouBattleMonsterManager()
{
	destroyInstance();
}
void DictMusouBattleMonsterManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
