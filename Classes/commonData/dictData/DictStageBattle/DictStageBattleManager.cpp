#include "DictStageBattleManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBattleManager* DictStageBattleManager::_instance = NULL;
void DictStageBattleManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBattle* data = new DictStageBattle();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->inChapterId = item->valueInt;
			item = item->next;			
			data->inStageId = item->valueInt;
			item = item->next;			
			data->indexOrder = item->valueInt;
			item = item->next;			
			data->playerLevel = item->valueInt;
			item = item->next;			
			data->oneDayTimes = item->valueInt;
			item = item->next;			
			data->costPower = item->valueInt;
			item = item->next;			
			data->playerLevelElite = item->valueInt;
			item = item->next;			
			data->oneDayTimesElite = item->valueInt;
			item = item->next;			
			data->costPowerElite = item->valueInt;
			item = item->next;			
			data->cardResource = item->valueString; 
			item = item->next;			
			data->mapResource = item->valueString; 
			item = item->next;			
			data->bgResource = item->valueString; 
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
			data->functionopen = item->valueString; 
			item = item->next;			
			data->isPause = item->valueInt;
			item = item->next;			
			data->starDetermine1 = item->valueInt;
			item = item->next;			
			data->starDetermine2 = item->valueFloat;
			item = item->next;			
			data->starDetermine3 = item->valueInt;
			item = item->next;			
			data->battleTime = item->valueInt;
			item = item->next;			
			data->victoryTime = item->valueInt;
			item = item->next;			
			data->battleExperience = item->valueInt;
			item = item->next;			
			data->publicExperience = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageBattle* DictStageBattleManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBattle* data = (DictStageBattle*)(data_list.at(key));
	return data;
}
DictStageBattleManager* DictStageBattleManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBattleManager();
	}
	return _instance;
}
Vector<DictStageBattle*>* DictStageBattleManager::getDataList()
{
	Vector<DictStageBattle*>* list = new Vector<DictStageBattle*>();
	for(auto value : data_list)
	{
		DictStageBattle* data  = ( DictStageBattle* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBattleManager::~DictStageBattleManager()
{
	destroyInstance();
}
void DictStageBattleManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
