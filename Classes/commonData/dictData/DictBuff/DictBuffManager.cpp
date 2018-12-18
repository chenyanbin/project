#include "DictBuffManager.h"
#include "../../../common/PublicShowUI.h"

DictBuffManager* DictBuffManager::_instance = NULL;
void DictBuffManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBuff* data = new DictBuff();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->attackType = item->valueInt;
			item = item->next;			
			data->target = item->valueInt;
			item = item->next;			
			data->time = item->valueInt;
			item = item->next;			
			data->onTime = item->valueInt;
			item = item->next;			
			data->hurt = item->valueInt;
			item = item->next;			
			data->effect = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->iconResource = item->valueString; 
			item = item->next;			
			data->x = item->valueInt;
			item = item->next;			
			data->y = item->valueInt;
			item = item->next;			
			data->point = item->valueInt;
			item = item->next;			
			data->level = item->valueInt;
			item = item->next;			
			data->voice = item->valueString; 
			item = item->next;			
			data->effectZoom = item->valueInt;
			item = item->next;			
			data->heroZoom = item->valueInt;
			item = item->next;			
			data->loopControl = item->valueInt;
			item = item->next;			
			data->characterShow = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictBuff* DictBuffManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBuff* data = (DictBuff*)(data_list.at(key));
	return data;
}
DictBuffManager* DictBuffManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBuffManager();
	}
	return _instance;
}
Vector<DictBuff*>* DictBuffManager::getDataList()
{
	Vector<DictBuff*>* list = new Vector<DictBuff*>();
	for(auto value : data_list)
	{
		DictBuff* data  = ( DictBuff* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBuffManager::~DictBuffManager()
{
	destroyInstance();
}
void DictBuffManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
