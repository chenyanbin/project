#include "DictLegendBattleTimesManager.h"
#include "../../../common/PublicShowUI.h"

DictLegendBattleTimesManager* DictLegendBattleTimesManager::_instance = NULL;
void DictLegendBattleTimesManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictLegendBattleTimes* data = new DictLegendBattleTimes();
			
			data->id = item->valueInt;
			item = item->next;			
			data->playerLevel = item->valueInt;
			item = item->next;			
			data->vip0Times = item->valueInt;
			item = item->next;			
			data->vip1Times = item->valueInt;
			item = item->next;			
			data->vip2Times = item->valueInt;
			item = item->next;			
			data->vip3Times = item->valueInt;
			item = item->next;			
			data->vip4Times = item->valueInt;
			item = item->next;			
			data->vip5Times = item->valueInt;
			item = item->next;			
			data->vip6Times = item->valueInt;
			item = item->next;			
			data->vip7Times = item->valueInt;
			item = item->next;			
			data->vip8Times = item->valueInt;
			item = item->next;			
			data->vip9Times = item->valueInt;
			item = item->next;			
			data->vip10Times = item->valueInt;
			item = item->next;			
			data->vip11Times = item->valueInt;
			item = item->next;			
			data->vip12Times = item->valueInt;
			item = item->next;			
			data->vip13Times = item->valueInt;
			item = item->next;			
			data->vip14Times = item->valueInt;
			item = item->next;			
			data->vip15Times = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictLegendBattleTimes* DictLegendBattleTimesManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictLegendBattleTimes* data = (DictLegendBattleTimes*)(data_list.at(key));
	return data;
}
DictLegendBattleTimesManager* DictLegendBattleTimesManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictLegendBattleTimesManager();
	}
	return _instance;
}
Vector<DictLegendBattleTimes*>* DictLegendBattleTimesManager::getDataList()
{
	Vector<DictLegendBattleTimes*>* list = new Vector<DictLegendBattleTimes*>();
	for(auto value : data_list)
	{
		DictLegendBattleTimes* data  = ( DictLegendBattleTimes* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictLegendBattleTimesManager::~DictLegendBattleTimesManager()
{
	destroyInstance();
}
void DictLegendBattleTimesManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
