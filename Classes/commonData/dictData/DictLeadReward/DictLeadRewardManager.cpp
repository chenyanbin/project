#include "DictLeadRewardManager.h"
#include "../../../common/PublicShowUI.h"

DictLeadRewardManager* DictLeadRewardManager::_instance = NULL;
void DictLeadRewardManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLeadReward* data = new DictLeadReward();
			
			data->effectId = item->valueInt;
			item = item->next;			
			data->quality1WeightStart = item->valueInt;
			item = item->next;			
			data->quality2WeightStart = item->valueInt;
			item = item->next;			
			data->quality3WeightStart = item->valueInt;
			item = item->next;			
			data->quality4WeightStart = item->valueInt;
			item = item->next;			
			data->quality5WeightStart = item->valueInt;
			item = item->next;			
			data->quality6WeightStart = item->valueInt;
			item = item->next;			
			data->quality7WeightStart = item->valueInt;
			item = item->next;			
			data->quality8WeightStart = item->valueInt;
			item = item->next;			
			data->quality1WeightGrow = item->valueInt;
			item = item->next;			
			data->quality2WeightGrow = item->valueInt;
			item = item->next;			
			data->quality3WeightGrow = item->valueInt;
			item = item->next;			
			data->quality4WeightGrow = item->valueInt;
			item = item->next;			
			data->quality5WeightGrow = item->valueInt;
			item = item->next;			
			data->quality6WeightGrow = item->valueInt;
			item = item->next;			
			data->quality7WeightGrow = item->valueInt;
			item = item->next;			
			data->quality8WeightGrow = item->valueInt;
			item = item->next;			
			data->itemHeroWeightStart = item->valueInt;
			item = item->next;			
			data->itemEquipWeightStart = item->valueInt;
			item = item->next;			
			data->itemBookWeightStart = item->valueInt;
			item = item->next;			
			data->itemMaterWeightStart = item->valueInt;
			item = item->next;			
			data->itemHeroWeightGrow = item->valueInt;
			item = item->next;			
			data->itemEquipWeightGrow = item->valueInt;
			item = item->next;			
			data->itemBookWeightGrow = item->valueInt;
			item = item->next;			
			data->itemMaterWeightGrow = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->effectId), data);
		}
		node = node->next;
	}
}
DictLeadReward* DictLeadRewardManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLeadReward* data = (DictLeadReward*)(data_list.at(key));
	return data;
}
DictLeadRewardManager* DictLeadRewardManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLeadRewardManager();
	}
	return _instance;
}
Vector<DictLeadReward*>* DictLeadRewardManager::getDataList()
{
	Vector<DictLeadReward*>* list = new Vector<DictLeadReward*>();
	for(auto value : data_list)
	{
		DictLeadReward* data  = ( DictLeadReward* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLeadRewardManager::~DictLeadRewardManager()
{
	destroyInstance();
}
void DictLeadRewardManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
