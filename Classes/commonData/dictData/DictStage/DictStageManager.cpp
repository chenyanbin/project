#include "DictStageManager.h"
#include "../../../common/PublicShowUI.h"

DictStageManager* DictStageManager::_instance = NULL;
void DictStageManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStage* data = new DictStage();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->inChaperId = item->valueInt;
			item = item->next;			
			data->indexOrder = item->valueInt;
			item = item->next;			
			data->axisX = item->valueInt;
			item = item->next;			
			data->axisY = item->valueInt;
			item = item->next;			
			data->showNumber = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStage* DictStageManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStage* data = (DictStage*)(data_list.at(key));
	return data;
}
DictStageManager* DictStageManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageManager();
	}
	return _instance;
}
Vector<DictStage*>* DictStageManager::getDataList()
{
	Vector<DictStage*>* list = new Vector<DictStage*>();
	for(auto value : data_list)
	{
		DictStage* data  = ( DictStage* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageManager::~DictStageManager()
{
	destroyInstance();
}
void DictStageManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
