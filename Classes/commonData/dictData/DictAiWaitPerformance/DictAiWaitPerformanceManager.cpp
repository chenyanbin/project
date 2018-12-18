#include "DictAiWaitPerformanceManager.h"
#include "../../../common/PublicShowUI.h"

DictAiWaitPerformanceManager* DictAiWaitPerformanceManager::_instance = NULL;
void DictAiWaitPerformanceManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictAiWaitPerformance* data = new DictAiWaitPerformance();
			
			data->ID = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->wonder = item->valueInt;
			item = item->next;			
			data->flank = item->valueInt;
			item = item->next;			
			data->standBy = item->valueInt;
			item = item->next;			
			data->standBack = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->ID), data);
		}
		node = node->next;
	}
}
DictAiWaitPerformance* DictAiWaitPerformanceManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictAiWaitPerformance* data = (DictAiWaitPerformance*)(data_list.at(key));
	return data;
}
DictAiWaitPerformanceManager* DictAiWaitPerformanceManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictAiWaitPerformanceManager();
	}
	return _instance;
}
Vector<DictAiWaitPerformance*>* DictAiWaitPerformanceManager::getDataList()
{
	Vector<DictAiWaitPerformance*>* list = new Vector<DictAiWaitPerformance*>();
	for(auto value : data_list)
	{
		DictAiWaitPerformance* data  = ( DictAiWaitPerformance* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictAiWaitPerformanceManager::~DictAiWaitPerformanceManager()
{
	destroyInstance();
}
void DictAiWaitPerformanceManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
