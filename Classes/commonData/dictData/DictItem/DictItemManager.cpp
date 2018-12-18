#include "DictItemManager.h"
#include "../../../common/PublicShowUI.h"

DictItemManager* DictItemManager::_instance = NULL;
void DictItemManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItem* data = new DictItem();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->typeUse = item->valueInt;
			item = item->next;			
			data->subType = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->stackNumber = item->valueInt;
			item = item->next;			
			data->backPackSell = item->valueInt;
			item = item->next;			
			data->sellingPrice = item->valueInt;
			item = item->next;			
			data->backPackUse = item->valueInt;
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItem* DictItemManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItem* data = (DictItem*)(data_list.at(key));
	return data;
}
DictItemManager* DictItemManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemManager();
	}
	return _instance;
}
Vector<DictItem*>* DictItemManager::getDataList()
{
	Vector<DictItem*>* list = new Vector<DictItem*>();
	for(auto value : data_list)
	{
		DictItem* data  = ( DictItem* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemManager::~DictItemManager()
{
	destroyInstance();
}
void DictItemManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
