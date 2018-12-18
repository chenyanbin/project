#include "DictStartRoleManager.h"
#include "../../../common/PublicShowUI.h"

DictStartRoleManager* DictStartRoleManager::_instance = NULL;
void DictStartRoleManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStartRole* data = new DictStartRole();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->ename = item->valueString; 
			item = item->next;			
			data->startValue = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStartRole* DictStartRoleManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStartRole* data = (DictStartRole*)(data_list.at(key));
	return data;
}
DictStartRoleManager* DictStartRoleManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStartRoleManager();
	}
	return _instance;
}
Vector<DictStartRole*>* DictStartRoleManager::getDataList()
{
	Vector<DictStartRole*>* list = new Vector<DictStartRole*>();
	for(auto value : data_list)
	{
		DictStartRole* data  = ( DictStartRole* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStartRoleManager::~DictStartRoleManager()
{
	destroyInstance();
}
void DictStartRoleManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
