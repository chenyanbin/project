#include "DictAiWaitTimeManager.h"
#include "../../../common/PublicShowUI.h"

DictAiWaitTimeManager* DictAiWaitTimeManager::_instance = NULL;
void DictAiWaitTimeManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictAiWaitTime* data = new DictAiWaitTime();
			
			data->ID = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->waitTime1 = item->valueInt;
			item = item->next;			
			data->wtRate1 = item->valueInt;
			item = item->next;			
			data->waitTime2 = item->valueInt;
			item = item->next;			
			data->wtRate2 = item->valueInt;
			item = item->next;			
			data->waitTime3 = item->valueInt;
			item = item->next;			
			data->wtRate3 = item->valueInt;
			item = item->next;			
			data->waitTime4 = item->valueInt;
			item = item->next;			
			data->wtRate4 = item->valueInt;
			item = item->next;			
			data->waitTime5 = item->valueInt;
			item = item->next;			
			data->wtRate5 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->ID), data);
		}
		node = node->next;
	}
}
DictAiWaitTime* DictAiWaitTimeManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictAiWaitTime* data = (DictAiWaitTime*)(data_list.at(key));
	return data;
}
DictAiWaitTimeManager* DictAiWaitTimeManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictAiWaitTimeManager();
	}
	return _instance;
}
Vector<DictAiWaitTime*>* DictAiWaitTimeManager::getDataList()
{
	Vector<DictAiWaitTime*>* list = new Vector<DictAiWaitTime*>();
	for(auto value : data_list)
	{
		DictAiWaitTime* data  = ( DictAiWaitTime* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictAiWaitTimeManager::~DictAiWaitTimeManager()
{
	destroyInstance();
}
void DictAiWaitTimeManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
