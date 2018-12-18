#include "DictEquipComposeManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipComposeManager* DictEquipComposeManager::_instance = NULL;
void DictEquipComposeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipCompose* data = new DictEquipCompose();
			
			data->equipId = item->valueInt;
			item = item->next;			
			data->materId = item->valueInt;
			item = item->next;			
			data->materNumber = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->equipId), data);
		}
		node = node->next;
	}
}
DictEquipCompose* DictEquipComposeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipCompose* data = (DictEquipCompose*)(data_list.at(key));
	return data;
}
DictEquipComposeManager* DictEquipComposeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipComposeManager();
	}
	return _instance;
}
Vector<DictEquipCompose*>* DictEquipComposeManager::getDataList()
{
	Vector<DictEquipCompose*>* list = new Vector<DictEquipCompose*>();
	for(auto value : data_list)
	{
		DictEquipCompose* data  = ( DictEquipCompose* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipComposeManager::~DictEquipComposeManager()
{
	destroyInstance();
}
void DictEquipComposeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
