#include "DictStageBuildingManager.h"
#include "../../../common/PublicShowUI.h"

DictStageBuildingManager* DictStageBuildingManager::_instance = NULL;
void DictStageBuildingManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStageBuilding* data = new DictStageBuilding();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->inChaperId = item->valueInt;
			item = item->next;			
			data->axisX = item->valueInt;
			item = item->next;			
			data->axisY = item->valueInt;
			item = item->next;			
			data->axisZ = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStageBuilding* DictStageBuildingManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStageBuilding* data = (DictStageBuilding*)(data_list.at(key));
	return data;
}
DictStageBuildingManager* DictStageBuildingManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStageBuildingManager();
	}
	return _instance;
}
Vector<DictStageBuilding*>* DictStageBuildingManager::getDataList()
{
	Vector<DictStageBuilding*>* list = new Vector<DictStageBuilding*>();
	for(auto value : data_list)
	{
		DictStageBuilding* data  = ( DictStageBuilding* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStageBuildingManager::~DictStageBuildingManager()
{
	destroyInstance();
}
void DictStageBuildingManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
