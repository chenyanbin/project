#include "DictItemQualityManager.h"
#include "../../../common/PublicShowUI.h"

DictItemQualityManager* DictItemQualityManager::_instance = NULL;
void DictItemQualityManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItemQuality* data = new DictItemQuality();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->ename = item->valueString; 
			item = item->next;			
			data->levelUpLimit = item->valueInt;
			item = item->next;			
			data->levelColour = item->valueString; 
			item = item->next;			
			data->levelColourResource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItemQuality* DictItemQualityManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItemQuality* data = (DictItemQuality*)(data_list.at(key));
	return data;
}
DictItemQualityManager* DictItemQualityManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemQualityManager();
	}
	return _instance;
}
Vector<DictItemQuality*>* DictItemQualityManager::getDataList()
{
	Vector<DictItemQuality*>* list = new Vector<DictItemQuality*>();
	for(auto value : data_list)
	{
		DictItemQuality* data  = ( DictItemQuality* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemQualityManager::~DictItemQualityManager()
{
	destroyInstance();
}
void DictItemQualityManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
