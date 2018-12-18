#include "DictLegendMonsterRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendMonsterRewardManager* DictLegendMonsterRewardManager::_instance = NULL;
void DictLegendMonsterRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendMonsterReward* data = new DictLegendMonsterReward();
			
			data->id = item->valueInt;
			item = item->next;			
			data->stageBattleId = item->valueInt;
			item = item->next;			
			data->normalOrPrestige = item->valueInt;
			item = item->next;			
			data->stageBattleName = item->valueInt;
			item = item->next;			
			data->itemType = item->valueInt;
			item = item->next;			
			data->itemId = item->valueInt;
			item = item->next;			
			data->heroPrestige = item->valueInt;
			item = item->next;			
			data->itemNumber = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendMonsterReward* DictLegendMonsterRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendMonsterReward* data = (DictLegendMonsterReward*)(data_list.at(key));
	return data;
}
DictLegendMonsterRewardManager* DictLegendMonsterRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendMonsterRewardManager();
	}
	return _instance;
}
Vector<DictLegendMonsterReward*>* DictLegendMonsterRewardManager::getDataList()
{
	Vector<DictLegendMonsterReward*>* list = new Vector<DictLegendMonsterReward*>();
	for(auto value : data_list)
	{
		DictLegendMonsterReward* data  = ( DictLegendMonsterReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendMonsterRewardManager::~DictLegendMonsterRewardManager()
{
	destroyInstance();
}
void DictLegendMonsterRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
