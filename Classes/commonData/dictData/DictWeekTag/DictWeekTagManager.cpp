#include "DictWeekTagManager.h"
#include "../../../common/PublicShowUI.h"

DictWeekTagManager* DictWeekTagManager::_instance = NULL;
void DictWeekTagManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWeekTag* data = new DictWeekTag();
			
			data->id = item->valueInt;
			item = item->next;			
			data->tag1Id = item->valueInt;
			item = item->next;			
			data->name1 = item->valueString; 
			item = item->next;			
			data->tag2Id = item->valueInt;
			item = item->next;			
			data->name2 = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWeekTag* DictWeekTagManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWeekTag* data = (DictWeekTag*)(data_list.at(key));
	return data;
}
DictWeekTagManager* DictWeekTagManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWeekTagManager();
	}
	return _instance;
}
Vector<DictWeekTag*>* DictWeekTagManager::getDataList()
{
	Vector<DictWeekTag*>* list = new Vector<DictWeekTag*>();
	for(auto value : data_list)
	{
		DictWeekTag* data  = ( DictWeekTag* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWeekTagManager::~DictWeekTagManager()
{
	destroyInstance();
}
void DictWeekTagManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
