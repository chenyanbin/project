#include "DictBlackshopManager.h"
#include "../../../common/PublicShowUI.h"

DictBlackshopManager* DictBlackshopManager::_instance = NULL;
void DictBlackshopManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBlackshop* data = new DictBlackshop();
			
			data->id = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->sellLocal = item->valueInt;
			item = item->next;			
			data->conId = item->valueInt;
			item = item->next;			
			data->conVal = item->valueInt;
			item = item->next;			
			data->number = item->valueInt;
			item = item->next;			
			data->weight = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictBlackshop* DictBlackshopManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBlackshop* data = (DictBlackshop*)(data_list.at(key));
	return data;
}
DictBlackshopManager* DictBlackshopManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBlackshopManager();
	}
	return _instance;
}
Vector<DictBlackshop*>* DictBlackshopManager::getDataList()
{
	Vector<DictBlackshop*>* list = new Vector<DictBlackshop*>();
	for(auto value : data_list)
	{
		DictBlackshop* data  = ( DictBlackshop* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBlackshopManager::~DictBlackshopManager()
{
	destroyInstance();
}
void DictBlackshopManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
