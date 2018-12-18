#include "DictArenaBotManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaBotManager* DictArenaBotManager::_instance = NULL;
void DictArenaBotManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaBot* data = new DictArenaBot();
			
			data->rank = item->valueInt;
			item = item->next;			
			data->hero1Id = item->valueInt;
			item = item->next;			
			data->hero1Level = item->valueInt;
			item = item->next;			
			data->hero1Quality = item->valueInt;
			item = item->next;			
			data->hero1Prestige = item->valueInt;
			item = item->next;			
			data->hero2Id = item->valueInt;
			item = item->next;			
			data->hero2Level = item->valueInt;
			item = item->next;			
			data->hero2Quality = item->valueInt;
			item = item->next;			
			data->hero2Prestige = item->valueInt;
			item = item->next;			
			data->hero3Id = item->valueInt;
			item = item->next;			
			data->hero3Level = item->valueInt;
			item = item->next;			
			data->hero3Quality = item->valueInt;
			item = item->next;			
			data->hero3Prestige = item->valueInt;
			item = item->next;			
			data->playerName = item->valueString; 
			item = item->next;			
			data->playerFightPower = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->rank), data);
		}
		node = node->next;
	}
}
DictArenaBot* DictArenaBotManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaBot* data = (DictArenaBot*)(data_list.at(key));
	return data;
}
DictArenaBotManager* DictArenaBotManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaBotManager();
	}
	return _instance;
}
Vector<DictArenaBot*>* DictArenaBotManager::getDataList()
{
	Vector<DictArenaBot*>* list = new Vector<DictArenaBot*>();
	for(auto value : data_list)
	{
		DictArenaBot* data  = ( DictArenaBot* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaBotManager::~DictArenaBotManager()
{
	destroyInstance();
}
void DictArenaBotManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
