#include "DictVipManager.h"
#include "../../../common/PublicShowUI.h"

DictVipManager* DictVipManager::_instance = NULL;
void DictVipManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictVip* data = new DictVip();
			
			data->vipLevel = item->valueInt;
			item = item->next;			
			data->totalChargeGold = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->coinChargeTimes = item->valueInt;
			item = item->next;			
			data->buyStaminaTimes = item->valueInt;
			item = item->next;			
			data->sweepCommand = item->valueInt;
			item = item->next;			
			data->findCommand = item->valueInt;
			item = item->next;			
			data->stageBattleSweepTenTimes = item->valueInt;
			item = item->next;			
			data->blackshopNormalSlot = item->valueInt;
			item = item->next;			
			data->blackshopPlusSlot = item->valueInt;
			item = item->next;			
			data->arenaTimesbuy = item->valueInt;
			item = item->next;			
			data->gemstoneTimesbuy = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->vipLevel), data);
		}
		node = node->next;
	}
}
DictVip* DictVipManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictVip* data = (DictVip*)(data_list.at(key));
	return data;
}
DictVipManager* DictVipManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictVipManager();
	}
	return _instance;
}
Vector<DictVip*>* DictVipManager::getDataList()
{
	Vector<DictVip*>* list = new Vector<DictVip*>();
	for(auto value : data_list)
	{
		DictVip* data  = ( DictVip* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictVipManager::~DictVipManager()
{
	destroyInstance();
}
void DictVipManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
