#include "DictItemMaterManager.h"
#include "../../../common/PublicShowUI.h"

DictItemMaterManager* DictItemMaterManager::_instance = NULL;
void DictItemMaterManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItemMater* data = new DictItemMater();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->stackNumber = item->valueInt;
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->targetId = item->valueInt;
			item = item->next;			
			data->levelColour = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItemMater* DictItemMaterManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItemMater* data = (DictItemMater*)(data_list.at(key));
	return data;
}
DictItemMaterManager* DictItemMaterManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemMaterManager();
	}
	return _instance;
}
Vector<DictItemMater*>* DictItemMaterManager::getDataList()
{
	Vector<DictItemMater*>* list = new Vector<DictItemMater*>();
	for(auto value : data_list)
	{
		DictItemMater* data  = ( DictItemMater* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemMaterManager::~DictItemMaterManager()
{
	destroyInstance();
}
void DictItemMaterManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
