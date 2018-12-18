#include "DictBattlePotionManager.h"
#include "../../../common/PublicShowUI.h"

DictBattlePotionManager* DictBattlePotionManager::_instance = NULL;
void DictBattlePotionManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBattlePotion* data = new DictBattlePotion();
			
			data->vipLevel = item->valueInt;
			item = item->next;			
			data->potionTimes = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->vipLevel), data);
		}
		node = node->next;
	}
}
DictBattlePotion* DictBattlePotionManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBattlePotion* data = (DictBattlePotion*)(data_list.at(key));
	return data;
}
DictBattlePotionManager* DictBattlePotionManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBattlePotionManager();
	}
	return _instance;
}
Vector<DictBattlePotion*>* DictBattlePotionManager::getDataList()
{
	Vector<DictBattlePotion*>* list = new Vector<DictBattlePotion*>();
	for(auto value : data_list)
	{
		DictBattlePotion* data  = ( DictBattlePotion* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBattlePotionManager::~DictBattlePotionManager()
{
	destroyInstance();
}
void DictBattlePotionManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
