#include "DictLegendRankManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendRankManager* DictLegendRankManager::_instance = NULL;
void DictLegendRankManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendRank* data = new DictLegendRank();
			
			data->id = item->valueInt;
			item = item->next;			
			data->rankmin = item->valueInt;
			item = item->next;			
			data->rankmax = item->valueInt;
			item = item->next;			
			data->honor = item->valueInt;
			item = item->next;			
			data->coin = item->valueInt;
			item = item->next;			
			data->item1Type = item->valueInt;
			item = item->next;			
			data->itemId1 = item->valueInt;
			item = item->next;			
			data->item1Number = item->valueInt;
			item = item->next;			
			data->hero1Prestige = item->valueInt;
			item = item->next;			
			data->item2Type = item->valueInt;
			item = item->next;			
			data->itemId2 = item->valueInt;
			item = item->next;			
			data->item2Number = item->valueInt;
			item = item->next;			
			data->hero2Prestige = item->valueInt;
			item = item->next;			
			data->item3Type = item->valueInt;
			item = item->next;			
			data->itemId3 = item->valueInt;
			item = item->next;			
			data->item3Number = item->valueInt;
			item = item->next;			
			data->hero3Prestige = item->valueInt;
			item = item->next;			
			data->item4Type = item->valueInt;
			item = item->next;			
			data->itemId4 = item->valueInt;
			item = item->next;			
			data->item4Number = item->valueInt;
			item = item->next;			
			data->hero4Prestige = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendRank* DictLegendRankManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendRank* data = (DictLegendRank*)(data_list.at(key));
	return data;
}
DictLegendRankManager* DictLegendRankManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendRankManager();
	}
	return _instance;
}
Vector<DictLegendRank*>* DictLegendRankManager::getDataList()
{
	Vector<DictLegendRank*>* list = new Vector<DictLegendRank*>();
	for(auto value : data_list)
	{
		DictLegendRank* data  = ( DictLegendRank* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendRankManager::~DictLegendRankManager()
{
	destroyInstance();
}
void DictLegendRankManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
