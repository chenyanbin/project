#include "DictNewGuideManager.h"
#include "../../../common/PublicShowUI.h"

DictNewGuideManager* DictNewGuideManager::_instance = NULL;
void DictNewGuideManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictNewGuide* data = new DictNewGuide();
			
			data->id = item->valueInt;
			item = item->next;			
			data->function = item->valueInt;
			item = item->next;			
			data->newGuideEvent = item->valueInt;
			item = item->next;			
			data->resource = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->orderIndex = item->valueInt;
			item = item->next;			
			data->place = item->valueInt;
			item = item->next;			
			data->arrow = item->valueInt;
			item = item->next;			
			data->x = item->valueInt;
			item = item->next;			
			data->y = item->valueInt;
			item = item->next;			
			data->arrowDirect = item->valueInt;
			item = item->next;			
			data->bottom = item->valueInt;
			item = item->next;			
			data->goFunction = item->valueInt;
			item = item->next;			
			data->isToSever = item->valueInt;
			item = item->next;			
			data->bottomId = item->valueInt;
			item = item->next;			
			data->isPause = item->valueInt;
			item = item->next;			
			data->breakpoint = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictNewGuide* DictNewGuideManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictNewGuide* data = (DictNewGuide*)(data_list.at(key));
	return data;
}
DictNewGuideManager* DictNewGuideManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictNewGuideManager();
	}
	return _instance;
}
Vector<DictNewGuide*>* DictNewGuideManager::getDataList()
{
	Vector<DictNewGuide*>* list = new Vector<DictNewGuide*>();
	for(auto value : data_list)
	{
		DictNewGuide* data  = ( DictNewGuide* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictNewGuideManager::~DictNewGuideManager()
{
	destroyInstance();
}
void DictNewGuideManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
