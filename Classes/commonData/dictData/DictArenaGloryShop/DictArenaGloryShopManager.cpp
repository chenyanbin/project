#include "DictArenaGloryShopManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaGloryShopManager* DictArenaGloryShopManager::_instance = NULL;
void DictArenaGloryShopManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaGloryShop* data = new DictArenaGloryShop();
			
			data->id = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->sellNumber = item->valueInt;
			item = item->next;			
			data->sellGold = item->valueInt;
			item = item->next;			
			data->isChange = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaGloryShop* DictArenaGloryShopManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaGloryShop* data = (DictArenaGloryShop*)(data_list.at(key));
	return data;
}
DictArenaGloryShopManager* DictArenaGloryShopManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaGloryShopManager();
	}
	return _instance;
}
Vector<DictArenaGloryShop*>* DictArenaGloryShopManager::getDataList()
{
	Vector<DictArenaGloryShop*>* list = new Vector<DictArenaGloryShop*>();
	for(auto value : data_list)
	{
		DictArenaGloryShop* data  = ( DictArenaGloryShop* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaGloryShopManager::~DictArenaGloryShopManager()
{
	destroyInstance();
}
void DictArenaGloryShopManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
