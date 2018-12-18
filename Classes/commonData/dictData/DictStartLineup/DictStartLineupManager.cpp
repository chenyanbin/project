#include "DictStartLineupManager.h"
#include "../../../common/PublicShowUI.h"

DictStartLineupManager* DictStartLineupManager::_instance = NULL;
void DictStartLineupManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStartLineup* data = new DictStartLineup();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->lineupId = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStartLineup* DictStartLineupManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStartLineup* data = (DictStartLineup*)(data_list.at(key));
	return data;
}
DictStartLineupManager* DictStartLineupManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStartLineupManager();
	}
	return _instance;
}
Vector<DictStartLineup*>* DictStartLineupManager::getDataList()
{
	Vector<DictStartLineup*>* list = new Vector<DictStartLineup*>();
	for(auto value : data_list)
	{
		DictStartLineup* data  = ( DictStartLineup* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStartLineupManager::~DictStartLineupManager()
{
	destroyInstance();
}
void DictStartLineupManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
