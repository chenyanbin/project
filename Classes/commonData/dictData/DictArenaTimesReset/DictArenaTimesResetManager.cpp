#include "DictArenaTimesResetManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaTimesResetManager* DictArenaTimesResetManager::_instance = NULL;
void DictArenaTimesResetManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaTimesReset* data = new DictArenaTimesReset();
			
			data->id = item->valueInt;
			item = item->next;			
			data->cdTimes = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaTimesReset* DictArenaTimesResetManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaTimesReset* data = (DictArenaTimesReset*)(data_list.at(key));
	return data;
}
DictArenaTimesResetManager* DictArenaTimesResetManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaTimesResetManager();
	}
	return _instance;
}
Vector<DictArenaTimesReset*>* DictArenaTimesResetManager::getDataList()
{
	Vector<DictArenaTimesReset*>* list = new Vector<DictArenaTimesReset*>();
	for(auto value : data_list)
	{
		DictArenaTimesReset* data  = ( DictArenaTimesReset* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaTimesResetManager::~DictArenaTimesResetManager()
{
	destroyInstance();
}
void DictArenaTimesResetManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
