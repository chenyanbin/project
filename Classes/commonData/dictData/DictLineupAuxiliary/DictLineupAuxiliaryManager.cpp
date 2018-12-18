#include "DictLineupAuxiliaryManager.h"
#include "../../../common/PublicShowUI.h"

DictLineupAuxiliaryManager* DictLineupAuxiliaryManager::_instance = NULL;
void DictLineupAuxiliaryManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLineupAuxiliary* data = new DictLineupAuxiliary();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->openLevel = item->valueInt;
			item = item->next;			
			data->attribute = item->valueInt;
			item = item->next;			
			data->qualityDefault = item->valueInt;
			item = item->next;			
			data->star1 = item->valueFloat;
			item = item->next;			
			data->star2 = item->valueFloat;
			item = item->next;			
			data->star3 = item->valueFloat;
			item = item->next;			
			data->star4 = item->valueFloat;
			item = item->next;			
			data->star5 = item->valueFloat;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLineupAuxiliary* DictLineupAuxiliaryManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLineupAuxiliary* data = (DictLineupAuxiliary*)(data_list.at(key));
	return data;
}
DictLineupAuxiliaryManager* DictLineupAuxiliaryManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLineupAuxiliaryManager();
	}
	return _instance;
}
Vector<DictLineupAuxiliary*>* DictLineupAuxiliaryManager::getDataList()
{
	Vector<DictLineupAuxiliary*>* list = new Vector<DictLineupAuxiliary*>();
	for(auto value : data_list)
	{
		DictLineupAuxiliary* data  = ( DictLineupAuxiliary* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLineupAuxiliaryManager::~DictLineupAuxiliaryManager()
{
	destroyInstance();
}
void DictLineupAuxiliaryManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
