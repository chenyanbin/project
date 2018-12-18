#include "DictTaskCommonTypeMsgManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskCommonTypeMsgManager* DictTaskCommonTypeMsgManager::_instance = NULL;
void DictTaskCommonTypeMsgManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskCommonTypeMsg* data = new DictTaskCommonTypeMsg();
			
			data->id = item->valueInt;
			item = item->next;			
			data->msgName = item->valueString; 
			item = item->next;			
			data->taskTypeId = item->valueInt;
			item = item->next;			
			data->taskTypeName = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTaskCommonTypeMsg* DictTaskCommonTypeMsgManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskCommonTypeMsg* data = (DictTaskCommonTypeMsg*)(data_list.at(key));
	return data;
}
DictTaskCommonTypeMsgManager* DictTaskCommonTypeMsgManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskCommonTypeMsgManager();
	}
	return _instance;
}
Vector<DictTaskCommonTypeMsg*>* DictTaskCommonTypeMsgManager::getDataList()
{
	Vector<DictTaskCommonTypeMsg*>* list = new Vector<DictTaskCommonTypeMsg*>();
	for(auto value : data_list)
	{
		DictTaskCommonTypeMsg* data  = ( DictTaskCommonTypeMsg* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskCommonTypeMsgManager::~DictTaskCommonTypeMsgManager()
{
	destroyInstance();
}
void DictTaskCommonTypeMsgManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
