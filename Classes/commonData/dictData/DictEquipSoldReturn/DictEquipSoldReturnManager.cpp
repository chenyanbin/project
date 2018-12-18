#include "DictEquipSoldReturnManager.h"
#include "../../../common/PublicShowUI.h"

DictEquipSoldReturnManager* DictEquipSoldReturnManager::_instance = NULL;
void DictEquipSoldReturnManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictEquipSoldReturn* data = new DictEquipSoldReturn();
			
			data->qlevel = item->valueInt;
			item = item->next;			
			data->moneyReturn = item->valueFloat;
		data_list.insert(PublicShowUI::numberToString(data->qlevel), data);
		}
		node = node->next;
	}
}
DictEquipSoldReturn* DictEquipSoldReturnManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictEquipSoldReturn* data = (DictEquipSoldReturn*)(data_list.at(key));
	return data;
}
DictEquipSoldReturnManager* DictEquipSoldReturnManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictEquipSoldReturnManager();
	}
	return _instance;
}
Vector<DictEquipSoldReturn*>* DictEquipSoldReturnManager::getDataList()
{
	Vector<DictEquipSoldReturn*>* list = new Vector<DictEquipSoldReturn*>();
	for(auto value : data_list)
	{
		DictEquipSoldReturn* data  = ( DictEquipSoldReturn* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictEquipSoldReturnManager::~DictEquipSoldReturnManager()
{
	destroyInstance();
}
void DictEquipSoldReturnManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
