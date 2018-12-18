#include "DictMusouBattleManager.h"
#include "../../../common/PublicShowUI.h"

DictMusouBattleManager* DictMusouBattleManager::_instance = NULL;
void DictMusouBattleManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMusouBattle* data = new DictMusouBattle();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->inStageId = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->indexOrder = item->valueInt;
			item = item->next;			
			data->playerLevel = item->valueInt;
			item = item->next;			
			data->costPower = item->valueInt;
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
			data->battleTime = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictMusouBattle* DictMusouBattleManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMusouBattle* data = (DictMusouBattle*)(data_list.at(key));
	return data;
}
DictMusouBattleManager* DictMusouBattleManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMusouBattleManager();
	}
	return _instance;
}
Vector<DictMusouBattle*>* DictMusouBattleManager::getDataList()
{
	Vector<DictMusouBattle*>* list = new Vector<DictMusouBattle*>();
	for(auto value : data_list)
	{
		DictMusouBattle* data  = ( DictMusouBattle* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMusouBattleManager::~DictMusouBattleManager()
{
	destroyInstance();
}
void DictMusouBattleManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
