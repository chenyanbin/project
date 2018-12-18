#include "DictLeadLootPhaseManager.h"
#include "../../../common/PublicShowUI.h"

DictLeadLootPhaseManager* DictLeadLootPhaseManager::_instance = NULL;
void DictLeadLootPhaseManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLeadLootPhase* data = new DictLeadLootPhase();
			
			data->id = item->valueInt;
			item = item->next;			
			data->conLimit = item->valueInt;
			item = item->next;			
			data->conMax = item->valueInt;
			item = item->next;			
			data->drawType = item->valueInt;
			item = item->next;			
			data->resType = item->valueInt;
			item = item->next;			
			data->conPhase = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLeadLootPhase* DictLeadLootPhaseManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLeadLootPhase* data = (DictLeadLootPhase*)(data_list.at(key));
	return data;
}
DictLeadLootPhaseManager* DictLeadLootPhaseManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLeadLootPhaseManager();
	}
	return _instance;
}
Vector<DictLeadLootPhase*>* DictLeadLootPhaseManager::getDataList()
{
	Vector<DictLeadLootPhase*>* list = new Vector<DictLeadLootPhase*>();
	for(auto value : data_list)
	{
		DictLeadLootPhase* data  = ( DictLeadLootPhase* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLeadLootPhaseManager::~DictLeadLootPhaseManager()
{
	destroyInstance();
}
void DictLeadLootPhaseManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
