#include "DictWayManager.h"
#include "../../../common/PublicShowUI.h"

DictWayManager* DictWayManager::_instance = NULL;
void DictWayManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictWay* data = new DictWay();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->desc2 = item->valueString; 
			item = item->next;			
			data->itemNumber = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->useTye = item->valueInt;
			item = item->next;			
			data->function = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictWay* DictWayManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictWay* data = (DictWay*)(data_list.at(key));
	return data;
}
DictWayManager* DictWayManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictWayManager();
	}
	return _instance;
}
Vector<DictWay*>* DictWayManager::getDataList()
{
	Vector<DictWay*>* list = new Vector<DictWay*>();
	for(auto value : data_list)
	{
		DictWay* data  = ( DictWay* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictWayManager::~DictWayManager()
{
	destroyInstance();
}
void DictWayManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
