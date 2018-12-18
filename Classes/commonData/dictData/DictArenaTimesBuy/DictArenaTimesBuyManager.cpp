#include "DictArenaTimesBuyManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaTimesBuyManager* DictArenaTimesBuyManager::_instance = NULL;
void DictArenaTimesBuyManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaTimesBuy* data = new DictArenaTimesBuy();
			
			data->buyTimes = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->buyTimes), data);
		}
		node = node->next;
	}
}
DictArenaTimesBuy* DictArenaTimesBuyManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaTimesBuy* data = (DictArenaTimesBuy*)(data_list.at(key));
	return data;
}
DictArenaTimesBuyManager* DictArenaTimesBuyManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaTimesBuyManager();
	}
	return _instance;
}
Vector<DictArenaTimesBuy*>* DictArenaTimesBuyManager::getDataList()
{
	Vector<DictArenaTimesBuy*>* list = new Vector<DictArenaTimesBuy*>();
	for(auto value : data_list)
	{
		DictArenaTimesBuy* data  = ( DictArenaTimesBuy* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaTimesBuyManager::~DictArenaTimesBuyManager()
{
	destroyInstance();
}
void DictArenaTimesBuyManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
