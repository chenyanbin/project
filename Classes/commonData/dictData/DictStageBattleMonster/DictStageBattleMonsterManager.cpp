#include "DictStageBattleMonsterManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBattleMonsterManager* DictStageBattleMonsterManager::_instance = NULL;
void DictStageBattleMonsterManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBattleMonster* data = new DictStageBattleMonster();
			
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
			data->monsterLevelElite = item->valueInt;
			item = item->next;			
			data->monsterQualityElite = item->valueInt;
			item = item->next;			
			data->sight = item->valueInt;
			item = item->next;			
			data->range = item->valueInt;
			item = item->next;			
			data->speed = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->health = item->valueInt;
			item = item->next;			
			data->attack = item->valueInt;
			item = item->next;			
			data->defend = item->valueInt;
			item = item->next;			
			data->critic = item->valueInt;
			item = item->next;			
			data->tenaci = item->valueInt;
			item = item->next;			
			data->hit = item->valueInt;
			item = item->next;			
			data->block = item->valueInt;
			item = item->next;			
			data->damageAdd = item->valueInt;
			item = item->next;			
			data->fireResist = item->valueInt;
			item = item->next;			
			data->iceResist = item->valueInt;
			item = item->next;			
			data->boltResist = item->valueInt;
			item = item->next;			
			data->windResist = item->valueInt;
			item = item->next;			
			data->poisonResist = item->valueInt;
			item = item->next;			
			data->healthE = item->valueInt;
			item = item->next;			
			data->attackE = item->valueInt;
			item = item->next;			
			data->defendE = item->valueInt;
			item = item->next;			
			data->criticE = item->valueInt;
			item = item->next;			
			data->tenaciE = item->valueInt;
			item = item->next;			
			data->hitE = item->valueInt;
			item = item->next;			
			data->blockE = item->valueInt;
			item = item->next;			
			data->damageAddE = item->valueInt;
			item = item->next;			
			data->fireResistE = item->valueInt;
			item = item->next;			
			data->iceResistE = item->valueInt;
			item = item->next;			
			data->boltResistE = item->valueInt;
			item = item->next;			
			data->windResistE = item->valueInt;
			item = item->next;			
			data->poisonResistE = item->valueInt;
			item = item->next;			
			data->aiID = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageBattleMonster* DictStageBattleMonsterManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBattleMonster* data = (DictStageBattleMonster*)(data_list.at(key));
	return data;
}
DictStageBattleMonsterManager* DictStageBattleMonsterManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBattleMonsterManager();
	}
	return _instance;
}
Vector<DictStageBattleMonster*>* DictStageBattleMonsterManager::getDataList()
{
	Vector<DictStageBattleMonster*>* list = new Vector<DictStageBattleMonster*>();
	for(auto value : data_list)
	{
		DictStageBattleMonster* data  = ( DictStageBattleMonster* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBattleMonsterManager::~DictStageBattleMonsterManager()
{
	destroyInstance();
}
void DictStageBattleMonsterManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
