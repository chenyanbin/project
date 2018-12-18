#include "DictShoppingVipTimesManager.h"
#include "../../../common/PublicShowUI.h"

DictShoppingVipTimesManager* DictShoppingVipTimesManager::_instance = NULL;
void DictShoppingVipTimesManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictShoppingVipTimes* data = new DictShoppingVipTimes();
			
			data->id = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->vip0Buy = item->valueInt;
			item = item->next;			
			data->vip1Buy = item->valueInt;
			item = item->next;			
			data->vip2Buy = item->valueInt;
			item = item->next;			
			data->vip3Buy = item->valueInt;
			item = item->next;			
			data->vip4Buy = item->valueInt;
			item = item->next;			
			data->vip5Buy = item->valueInt;
			item = item->next;			
			data->vip6Buy = item->valueInt;
			item = item->next;			
			data->vip7Buy = item->valueInt;
			item = item->next;			
			data->vip8Buy = item->valueInt;
			item = item->next;			
			data->vip9Buy = item->valueInt;
			item = item->next;			
			data->vip10Buy = item->valueInt;
			item = item->next;			
			data->vip11Buy = item->valueInt;
			item = item->next;			
			data->vip12Buy = item->valueInt;
			item = item->next;			
			data->vip13Buy = item->valueInt;
			item = item->next;			
			data->vip14Buy = item->valueInt;
			item = item->next;			
			data->vip15Buy = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictShoppingVipTimes* DictShoppingVipTimesManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictShoppingVipTimes* data = (DictShoppingVipTimes*)(data_list.at(key));
	return data;
}
DictShoppingVipTimesManager* DictShoppingVipTimesManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictShoppingVipTimesManager();
	}
	return _instance;
}
Vector<DictShoppingVipTimes*>* DictShoppingVipTimesManager::getDataList()
{
	Vector<DictShoppingVipTimes*>* list = new Vector<DictShoppingVipTimes*>();
	for(auto value : data_list)
	{
		DictShoppingVipTimes* data  = ( DictShoppingVipTimes* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictShoppingVipTimesManager::~DictShoppingVipTimesManager()
{
	destroyInstance();
}
void DictShoppingVipTimesManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
