#include "DictMarketManager.h"
#include "../../../common/PublicShowUI.h"

DictMarketManager* DictMarketManager::_instance = NULL;
void DictMarketManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMarket* data = new DictMarket();
			
			data->id = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->sellingPriceMin = item->valueInt;
			item = item->next;			
			data->sellingPriceMax = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictMarket* DictMarketManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMarket* data = (DictMarket*)(data_list.at(key));
	return data;
}
DictMarketManager* DictMarketManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMarketManager();
	}
	return _instance;
}
Vector<DictMarket*>* DictMarketManager::getDataList()
{
	Vector<DictMarket*>* list = new Vector<DictMarket*>();
	for(auto value : data_list)
	{
		DictMarket* data  = ( DictMarket* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMarketManager::~DictMarketManager()
{
	destroyInstance();
}
void DictMarketManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
