#include "DictLuckyGoldTimeManager.h"
#include "../../../common/PublicShowUI.h"

DictLuckyGoldTimeManager* DictLuckyGoldTimeManager::_instance = NULL;
void DictLuckyGoldTimeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLuckyGoldTime* data = new DictLuckyGoldTime();
			
			data->id = item->valueInt;
			item = item->next;			
			data->timeRequired = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLuckyGoldTime* DictLuckyGoldTimeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLuckyGoldTime* data = (DictLuckyGoldTime*)(data_list.at(key));
	return data;
}
DictLuckyGoldTimeManager* DictLuckyGoldTimeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLuckyGoldTimeManager();
	}
	return _instance;
}
Vector<DictLuckyGoldTime*>* DictLuckyGoldTimeManager::getDataList()
{
	Vector<DictLuckyGoldTime*>* list = new Vector<DictLuckyGoldTime*>();
	for(auto value : data_list)
	{
		DictLuckyGoldTime* data  = ( DictLuckyGoldTime* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLuckyGoldTimeManager::~DictLuckyGoldTimeManager()
{
	destroyInstance();
}
void DictLuckyGoldTimeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
