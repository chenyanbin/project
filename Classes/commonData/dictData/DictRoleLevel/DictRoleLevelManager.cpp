#include "DictRoleLevelManager.h"
#include "../../../common/PublicShowUI.h"

DictRoleLevelManager* DictRoleLevelManager::_instance = NULL;
void DictRoleLevelManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictRoleLevel* data = new DictRoleLevel();
			
			data->playerLevel = item->valueInt;
			item = item->next;			
			data->needExp = item->valueInt;
			item = item->next;			
			data->leadership = item->valueInt;
			item = item->next;			
			data->heroBelongUp = item->valueInt;
			item = item->next;			
			data->equipBelongUp = item->valueInt;
			item = item->next;			
			data->stageBattleExp = item->valueInt;
			item = item->next;			
			data->stageBattleCoin = item->valueInt;
			item = item->next;			
			data->arenaBattleExp = item->valueInt;
			item = item->next;			
			data->arenaBattleCoin = item->valueInt;
			item = item->next;			
			data->arenaBattleGlory = item->valueInt;
			item = item->next;			
			data->powerRecoverLimit = item->valueInt;
			item = item->next;			
			data->powerBonus = item->valueInt;
			item = item->next;			
			data->openFunction = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->playerLevel), data);
		}
		node = node->next;
	}
}
DictRoleLevel* DictRoleLevelManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictRoleLevel* data = (DictRoleLevel*)(data_list.at(key));
	return data;
}
DictRoleLevelManager* DictRoleLevelManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictRoleLevelManager();
	}
	return _instance;
}
Vector<DictRoleLevel*>* DictRoleLevelManager::getDataList()
{
	Vector<DictRoleLevel*>* list = new Vector<DictRoleLevel*>();
	for(auto value : data_list)
	{
		DictRoleLevel* data  = ( DictRoleLevel* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictRoleLevelManager::~DictRoleLevelManager()
{
	destroyInstance();
}
void DictRoleLevelManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
