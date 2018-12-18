#include "DictGemstoneMineRateManager.h"
#include "../../../common/PublicShowUI.h"

DictGemstoneMineRateManager* DictGemstoneMineRateManager::_instance = NULL;
void DictGemstoneMineRateManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictGemstoneMineRate* data = new DictGemstoneMineRate();
			
			data->id = item->valueInt;
			item = item->next;			
			data->critMultiple1 = item->valueInt;
			item = item->next;			
			data->critInitialValue1 = item->valueInt;
			item = item->next;			
			data->critGrowthValue1 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictGemstoneMineRate* DictGemstoneMineRateManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictGemstoneMineRate* data = (DictGemstoneMineRate*)(data_list.at(key));
	return data;
}
DictGemstoneMineRateManager* DictGemstoneMineRateManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictGemstoneMineRateManager();
	}
	return _instance;
}
Vector<DictGemstoneMineRate*>* DictGemstoneMineRateManager::getDataList()
{
	Vector<DictGemstoneMineRate*>* list = new Vector<DictGemstoneMineRate*>();
	for(auto value : data_list)
	{
		DictGemstoneMineRate* data  = ( DictGemstoneMineRate* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictGemstoneMineRateManager::~DictGemstoneMineRateManager()
{
	destroyInstance();
}
void DictGemstoneMineRateManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
