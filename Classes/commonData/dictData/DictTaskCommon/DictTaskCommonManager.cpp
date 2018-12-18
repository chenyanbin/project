#include "DictTaskCommonManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskCommonManager* DictTaskCommonManager::_instance = NULL;
void DictTaskCommonManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskCommon* data = new DictTaskCommon();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->category = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->conditionTaskId = item->valueInt;
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->taskType = item->valueInt;
			item = item->next;			
			data->finishCon1 = item->valueString; 
			item = item->next;			
			data->finishCon2 = item->valueString; 
			item = item->next;			
			data->finishCon3 = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskCommon* DictTaskCommonManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskCommon* data = (DictTaskCommon*)(data_list.at(key));
	return data;
}
DictTaskCommonManager* DictTaskCommonManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskCommonManager();
	}
	return _instance;
}
Vector<DictTaskCommon*>* DictTaskCommonManager::getDataList()
{
	Vector<DictTaskCommon*>* list = new Vector<DictTaskCommon*>();
	for(auto value : data_list)
	{
		DictTaskCommon* data  = ( DictTaskCommon* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskCommonManager::~DictTaskCommonManager()
{
	destroyInstance();
}
void DictTaskCommonManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
