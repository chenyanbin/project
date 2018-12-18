#include "DictFindLootWeightManager.h"
#include "../../../common/PublicShowUI.h"

DictFindLootWeightManager* DictFindLootWeightManager::_instance = NULL;
void DictFindLootWeightManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictFindLootWeight* data = new DictFindLootWeight();
			
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
		data_list.insert(PublicShowUI::numberToString(data->quality1ItemId), data);
		}
		node = node->next;
	}
}
DictFindLootWeight* DictFindLootWeightManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictFindLootWeight* data = (DictFindLootWeight*)(data_list.at(key));
	return data;
}
DictFindLootWeightManager* DictFindLootWeightManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictFindLootWeightManager();
	}
	return _instance;
}
Vector<DictFindLootWeight*>* DictFindLootWeightManager::getDataList()
{
	Vector<DictFindLootWeight*>* list = new Vector<DictFindLootWeight*>();
	for(auto value : data_list)
	{
		DictFindLootWeight* data  = ( DictFindLootWeight* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictFindLootWeightManager::~DictFindLootWeightManager()
{
	destroyInstance();
}
void DictFindLootWeightManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
