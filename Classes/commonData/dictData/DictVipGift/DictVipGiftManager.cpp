#include "DictVipGiftManager.h"
#include "../../../common/PublicShowUI.h"

DictVipGiftManager* DictVipGiftManager::_instance = NULL;
void DictVipGiftManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictVipGift* data = new DictVipGift();
			
			data->id = item->valueInt;
			item = item->next;			
			data->day = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->itemNumber = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictVipGift* DictVipGiftManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictVipGift* data = (DictVipGift*)(data_list.at(key));
	return data;
}
DictVipGiftManager* DictVipGiftManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictVipGiftManager();
	}
	return _instance;
}
Vector<DictVipGift*>* DictVipGiftManager::getDataList()
{
	Vector<DictVipGift*>* list = new Vector<DictVipGift*>();
	for(auto value : data_list)
	{
		DictVipGift* data  = ( DictVipGift* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictVipGiftManager::~DictVipGiftManager()
{
	destroyInstance();
}
void DictVipGiftManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
