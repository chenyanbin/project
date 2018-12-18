#include "DictShoppingManager.h"
#include "../../../common/PublicShowUI.h"

DictShoppingManager* DictShoppingManager::_instance = NULL;
void DictShoppingManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictShopping* data = new DictShopping();
			
			data->id = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->itemName = item->valueString; 
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
			item = item->next;			
			data->goldNow = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictShopping* DictShoppingManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictShopping* data = (DictShopping*)(data_list.at(key));
	return data;
}
DictShoppingManager* DictShoppingManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictShoppingManager();
	}
	return _instance;
}
Vector<DictShopping*>* DictShoppingManager::getDataList()
{
	Vector<DictShopping*>* list = new Vector<DictShopping*>();
	for(auto value : data_list)
	{
		DictShopping* data  = ( DictShopping* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictShoppingManager::~DictShoppingManager()
{
	destroyInstance();
}
void DictShoppingManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
