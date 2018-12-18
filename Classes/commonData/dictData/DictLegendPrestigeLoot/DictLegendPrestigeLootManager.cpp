#include "DictLegendPrestigeLootManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendPrestigeLootManager* DictLegendPrestigeLootManager::_instance = NULL;
void DictLegendPrestigeLootManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendPrestigeLoot* data = new DictLegendPrestigeLoot();
			
			data->id = item->valueInt;
			item = item->next;			
			data->prestige = item->valueInt;
			item = item->next;			
			data->class1 = item->valueInt;
			item = item->next;			
			data->class2 = item->valueInt;
			item = item->next;			
			data->class3 = item->valueInt;
			item = item->next;			
			data->class4 = item->valueInt;
			item = item->next;			
			data->class5 = item->valueInt;
			item = item->next;			
			data->class6 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendPrestigeLoot* DictLegendPrestigeLootManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendPrestigeLoot* data = (DictLegendPrestigeLoot*)(data_list.at(key));
	return data;
}
DictLegendPrestigeLootManager* DictLegendPrestigeLootManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendPrestigeLootManager();
	}
	return _instance;
}
Vector<DictLegendPrestigeLoot*>* DictLegendPrestigeLootManager::getDataList()
{
	Vector<DictLegendPrestigeLoot*>* list = new Vector<DictLegendPrestigeLoot*>();
	for(auto value : data_list)
	{
		DictLegendPrestigeLoot* data  = ( DictLegendPrestigeLoot* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendPrestigeLootManager::~DictLegendPrestigeLootManager()
{
	destroyInstance();
}
void DictLegendPrestigeLootManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
