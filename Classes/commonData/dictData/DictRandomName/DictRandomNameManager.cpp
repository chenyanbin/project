#include "DictRandomNameManager.h"
#include "../../../common/PublicShowUI.h"

DictRandomNameManager* DictRandomNameManager::_instance = NULL;
void DictRandomNameManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictRandomName* data = new DictRandomName();
			
			data->id = item->valueInt;
			item = item->next;			
			data->surName = item->valueString; 
			item = item->next;			
			data->maleName = item->valueString; 
			item = item->next;			
			data->femaleName = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictRandomName* DictRandomNameManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictRandomName* data = (DictRandomName*)(data_list.at(key));
	return data;
}
DictRandomNameManager* DictRandomNameManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictRandomNameManager();
	}
	return _instance;
}
Vector<DictRandomName*>* DictRandomNameManager::getDataList()
{
	Vector<DictRandomName*>* list = new Vector<DictRandomName*>();
	for(auto value : data_list)
	{
		DictRandomName* data  = ( DictRandomName* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictRandomNameManager::~DictRandomNameManager()
{
	destroyInstance();
}
void DictRandomNameManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
