#include "DictLegendManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendManager* DictLegendManager::_instance = NULL;
void DictLegendManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegend* data = new DictLegend();
			
			data->id = item->valueInt;
			item = item->next;			
			data->periods = item->valueString; 
			item = item->next;			
			data->legendName = item->valueString; 
			item = item->next;			
			data->openDate = item->valueString; 
			item = item->next;			
			data->openTime = item->valueString; 
			item = item->next;			
			data->closeDate = item->valueString; 
			item = item->next;			
			data->closeTime = item->valueString; 
			item = item->next;			
			data->multiItemHeroId = item->valueInt;
			item = item->next;			
			data->rankItemHeroId = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegend* DictLegendManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegend* data = (DictLegend*)(data_list.at(key));
	return data;
}
DictLegendManager* DictLegendManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendManager();
	}
	return _instance;
}
Vector<DictLegend*>* DictLegendManager::getDataList()
{
	Vector<DictLegend*>* list = new Vector<DictLegend*>();
	for(auto value : data_list)
	{
		DictLegend* data  = ( DictLegend* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendManager::~DictLegendManager()
{
	destroyInstance();
}
void DictLegendManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
