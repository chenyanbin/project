#include "DictLegendDamageRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendDamageRewardManager* DictLegendDamageRewardManager::_instance = NULL;
void DictLegendDamageRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendDamageReward* data = new DictLegendDamageReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->monsterLevel = item->valueInt;
			item = item->next;			
			data->hurtCoin1 = item->valueInt;
			item = item->next;			
			data->hurtCoin2 = item->valueInt;
			item = item->next;			
			data->hurtCoin3 = item->valueInt;
			item = item->next;			
			data->hurtCoin5 = item->valueInt;
			item = item->next;			
			data->hurtCoin10 = item->valueInt;
			item = item->next;			
			data->hurtCoin20 = item->valueInt;
			item = item->next;			
			data->hurtCoin40 = item->valueInt;
			item = item->next;			
			data->hurtCoin60 = item->valueInt;
			item = item->next;			
			data->hurtCoin80 = item->valueInt;
			item = item->next;			
			data->hurtCoin100 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendDamageReward* DictLegendDamageRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendDamageReward* data = (DictLegendDamageReward*)(data_list.at(key));
	return data;
}
DictLegendDamageRewardManager* DictLegendDamageRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendDamageRewardManager();
	}
	return _instance;
}
Vector<DictLegendDamageReward*>* DictLegendDamageRewardManager::getDataList()
{
	Vector<DictLegendDamageReward*>* list = new Vector<DictLegendDamageReward*>();
	for(auto value : data_list)
	{
		DictLegendDamageReward* data  = ( DictLegendDamageReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendDamageRewardManager::~DictLegendDamageRewardManager()
{
	destroyInstance();
}
void DictLegendDamageRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
