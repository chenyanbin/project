#include "DictItemUseRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictItemUseRewardManager* DictItemUseRewardManager::_instance = NULL;
void DictItemUseRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictItemUseReward* data = new DictItemUseReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->stageBattleName = item->valueString; 
			item = item->next;			
			data->itemType1 = item->valueInt;
			item = item->next;			
			data->itemId1 = item->valueInt;
			item = item->next;			
			data->itemNumber1 = item->valueInt;
			item = item->next;			
			data->lootOddsBase1 = item->valueInt;
			item = item->next;			
			data->itemType2 = item->valueInt;
			item = item->next;			
			data->itemId2 = item->valueInt;
			item = item->next;			
			data->itemNumber2 = item->valueInt;
			item = item->next;			
			data->lootOddsBase2 = item->valueInt;
			item = item->next;			
			data->itemType3 = item->valueInt;
			item = item->next;			
			data->itemId3 = item->valueInt;
			item = item->next;			
			data->itemNumber3 = item->valueInt;
			item = item->next;			
			data->lootOddsBase3 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictItemUseReward* DictItemUseRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictItemUseReward* data = (DictItemUseReward*)(data_list.at(key));
	return data;
}
DictItemUseRewardManager* DictItemUseRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictItemUseRewardManager();
	}
	return _instance;
}
Vector<DictItemUseReward*>* DictItemUseRewardManager::getDataList()
{
	Vector<DictItemUseReward*>* list = new Vector<DictItemUseReward*>();
	for(auto value : data_list)
	{
		DictItemUseReward* data  = ( DictItemUseReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictItemUseRewardManager::~DictItemUseRewardManager()
{
	destroyInstance();
}
void DictItemUseRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
