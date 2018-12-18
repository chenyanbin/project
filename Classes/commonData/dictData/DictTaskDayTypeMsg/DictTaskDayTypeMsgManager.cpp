#include "DictTaskDayTypeMsgManager.h"
#include "../../../common/PublicShowUI.h"

DictTaskDayTypeMsgManager* DictTaskDayTypeMsgManager::_instance = NULL;
void DictTaskDayTypeMsgManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTaskDayTypeMsg* data = new DictTaskDayTypeMsg();
			
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
DictTaskDayTypeMsg* DictTaskDayTypeMsgManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTaskDayTypeMsg* data = (DictTaskDayTypeMsg*)(data_list.at(key));
	return data;
}
DictTaskDayTypeMsgManager* DictTaskDayTypeMsgManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTaskDayTypeMsgManager();
	}
	return _instance;
}
Vector<DictTaskDayTypeMsg*>* DictTaskDayTypeMsgManager::getDataList()
{
	Vector<DictTaskDayTypeMsg*>* list = new Vector<DictTaskDayTypeMsg*>();
	for(auto value : data_list)
	{
		DictTaskDayTypeMsg* data  = ( DictTaskDayTypeMsg* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTaskDayTypeMsgManager::~DictTaskDayTypeMsgManager()
{
	destroyInstance();
}
void DictTaskDayTypeMsgManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
