#include "DictBuyStaminaManager.h"
#include "../../../common/PublicShowUI.h"

DictBuyStaminaManager* DictBuyStaminaManager::_instance = NULL;
void DictBuyStaminaManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBuyStamina* data = new DictBuyStamina();
			
			data->id = item->valueInt;
			item = item->next;			
			data->goldCost = item->valueInt;
			item = item->next;			
			data->stamina = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictBuyStamina* DictBuyStaminaManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBuyStamina* data = (DictBuyStamina*)(data_list.at(key));
	return data;
}
DictBuyStaminaManager* DictBuyStaminaManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBuyStaminaManager();
	}
	return _instance;
}
Vector<DictBuyStamina*>* DictBuyStaminaManager::getDataList()
{
	Vector<DictBuyStamina*>* list = new Vector<DictBuyStamina*>();
	for(auto value : data_list)
	{
		DictBuyStamina* data  = ( DictBuyStamina* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBuyStaminaManager::~DictBuyStaminaManager()
{
	destroyInstance();
}
void DictBuyStaminaManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
