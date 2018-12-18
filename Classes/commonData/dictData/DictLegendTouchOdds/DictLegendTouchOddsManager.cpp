#include "DictLegendTouchOddsManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendTouchOddsManager* DictLegendTouchOddsManager::_instance = NULL;
void DictLegendTouchOddsManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendTouchOdds* data = new DictLegendTouchOdds();
			
			data->id = item->valueInt;
			item = item->next;			
			data->playerLevel = item->valueInt;
			item = item->next;			
			data->vip0Touch = item->valueInt;
			item = item->next;			
			data->vip1Touch = item->valueInt;
			item = item->next;			
			data->vip2Touch = item->valueInt;
			item = item->next;			
			data->vip3Touch = item->valueInt;
			item = item->next;			
			data->vip4Touch = item->valueInt;
			item = item->next;			
			data->vip5Touch = item->valueInt;
			item = item->next;			
			data->vip6Touch = item->valueInt;
			item = item->next;			
			data->vip7Touch = item->valueInt;
			item = item->next;			
			data->vip8Touch = item->valueInt;
			item = item->next;			
			data->vip9Touch = item->valueInt;
			item = item->next;			
			data->vip10Touch = item->valueInt;
			item = item->next;			
			data->vip11Touch = item->valueInt;
			item = item->next;			
			data->vip12Touch = item->valueInt;
			item = item->next;			
			data->vip13Touch = item->valueInt;
			item = item->next;			
			data->vip14Touch = item->valueInt;
			item = item->next;			
			data->vip15Touch = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendTouchOdds* DictLegendTouchOddsManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendTouchOdds* data = (DictLegendTouchOdds*)(data_list.at(key));
	return data;
}
DictLegendTouchOddsManager* DictLegendTouchOddsManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendTouchOddsManager();
	}
	return _instance;
}
Vector<DictLegendTouchOdds*>* DictLegendTouchOddsManager::getDataList()
{
	Vector<DictLegendTouchOdds*>* list = new Vector<DictLegendTouchOdds*>();
	for(auto value : data_list)
	{
		DictLegendTouchOdds* data  = ( DictLegendTouchOdds* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendTouchOddsManager::~DictLegendTouchOddsManager()
{
	destroyInstance();
}
void DictLegendTouchOddsManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
