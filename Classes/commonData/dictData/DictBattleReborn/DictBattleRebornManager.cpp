#include "DictBattleRebornManager.h"
#include "../../../common/PublicShowUI.h"

DictBattleRebornManager* DictBattleRebornManager::_instance = NULL;
void DictBattleRebornManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBattleReborn* data = new DictBattleReborn();
			
			data->vipLevel = item->valueInt;
			item = item->next;			
			data->rebornTimes = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->vipLevel), data);
		}
		node = node->next;
	}
}
DictBattleReborn* DictBattleRebornManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBattleReborn* data = (DictBattleReborn*)(data_list.at(key));
	return data;
}
DictBattleRebornManager* DictBattleRebornManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBattleRebornManager();
	}
	return _instance;
}
Vector<DictBattleReborn*>* DictBattleRebornManager::getDataList()
{
	Vector<DictBattleReborn*>* list = new Vector<DictBattleReborn*>();
	for(auto value : data_list)
	{
		DictBattleReborn* data  = ( DictBattleReborn* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBattleRebornManager::~DictBattleRebornManager()
{
	destroyInstance();
}
void DictBattleRebornManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
