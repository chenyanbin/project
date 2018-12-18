#include "DictLeadLootWeightManager.h"
#include "../../../common/PublicShowUI.h"

DictLeadLootWeightManager* DictLeadLootWeightManager::_instance = NULL;
void DictLeadLootWeightManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLeadLootWeight* data = new DictLeadLootWeight();
			
			data->quality1ItemId = item->valueInt;
			item = item->next;			
			data->quality2ItemId = item->valueInt;
			item = item->next;			
			data->quality3ItemId = item->valueInt;
			item = item->next;			
			data->quality4ItemId = item->valueInt;
			item = item->next;			
			data->quality5ItemId = item->valueInt;
			item = item->next;			
			data->quality6ItemId = item->valueInt;
			item = item->next;			
			data->quality7ItemId = item->valueInt;
			item = item->next;			
			data->quality8ItemId = item->valueInt;
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->chooseWeightStart = item->valueInt;
			item = item->next;			
			data->chooseWeightRule = item->valueInt;
			item = item->next;			
			data->effectId1 = item->valueInt;
			item = item->next;			
			data->effectId2 = item->valueInt;
			item = item->next;			
			data->effectId3 = item->valueInt;
			item = item->next;			
			data->effectId4 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->quality1ItemId), data);
		}
		node = node->next;
	}
}
DictLeadLootWeight* DictLeadLootWeightManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLeadLootWeight* data = (DictLeadLootWeight*)(data_list.at(key));
	return data;
}
DictLeadLootWeightManager* DictLeadLootWeightManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLeadLootWeightManager();
	}
	return _instance;
}
Vector<DictLeadLootWeight*>* DictLeadLootWeightManager::getDataList()
{
	Vector<DictLeadLootWeight*>* list = new Vector<DictLeadLootWeight*>();
	for(auto value : data_list)
	{
		DictLeadLootWeight* data  = ( DictLeadLootWeight* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLeadLootWeightManager::~DictLeadLootWeightManager()
{
	destroyInstance();
}
void DictLeadLootWeightManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
