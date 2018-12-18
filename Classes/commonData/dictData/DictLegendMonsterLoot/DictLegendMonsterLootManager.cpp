#include "DictLegendMonsterLootManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendMonsterLootManager* DictLegendMonsterLootManager::_instance = NULL;
void DictLegendMonsterLootManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendMonsterLoot* data = new DictLegendMonsterLoot();
			
			data->id = item->valueInt;
			item = item->next;			
			data->monsterLv = item->valueInt;
			item = item->next;			
			data->class1 = item->valueInt;
			item = item->next;			
			data->class2 = item->valueInt;
			item = item->next;			
			data->class3 = item->valueInt;
			item = item->next;			
			data->class4 = item->valueInt;
			item = item->next;			
			data->class5 = item->valueInt;
			item = item->next;			
			data->class6 = item->valueInt;
			item = item->next;			
			data->class7 = item->valueInt;
			item = item->next;			
			data->class8 = item->valueInt;
			item = item->next;			
			data->class9 = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendMonsterLoot* DictLegendMonsterLootManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendMonsterLoot* data = (DictLegendMonsterLoot*)(data_list.at(key));
	return data;
}
DictLegendMonsterLootManager* DictLegendMonsterLootManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendMonsterLootManager();
	}
	return _instance;
}
Vector<DictLegendMonsterLoot*>* DictLegendMonsterLootManager::getDataList()
{
	Vector<DictLegendMonsterLoot*>* list = new Vector<DictLegendMonsterLoot*>();
	for(auto value : data_list)
	{
		DictLegendMonsterLoot* data  = ( DictLegendMonsterLoot* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendMonsterLootManager::~DictLegendMonsterLootManager()
{
	destroyInstance();
}
void DictLegendMonsterLootManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
