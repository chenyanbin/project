#include "DictMonsterManager.h"
#include "../../../common/PublicShowUI.h"

DictMonsterManager* DictMonsterManager::_instance = NULL;
void DictMonsterManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictMonster* data = new DictMonster();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->attackType = item->valueInt;
			item = item->next;			
			data->heroProp = item->valueString; 
			item = item->next;			
			data->skill1 = item->valueInt;
			item = item->next;			
			data->skill2 = item->valueInt;
			item = item->next;			
			data->skill3 = item->valueInt;
			item = item->next;			
			data->skill4 = item->valueInt;
			item = item->next;			
			data->skill5 = item->valueInt;
			item = item->next;			
			data->skill6 = item->valueInt;
			item = item->next;			
			data->skill7 = item->valueInt;
			item = item->next;			
			data->skill8 = item->valueInt;
			item = item->next;			
			data->skill9 = item->valueInt;
			item = item->next;			
			data->skill10 = item->valueInt;
			item = item->next;			
			data->skillJumpTime = item->valueFloat;
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->resourceHighShifting = item->valueInt;
			item = item->next;			
			data->resourceShifting = item->valueInt;
			item = item->next;			
			data->dieVoice = item->valueString; 
			item = item->next;			
			data->aiId = item->valueInt;
			item = item->next;			
			data->delayTime = item->valueInt;
			item = item->next;			
			data->ssTime = item->valueInt;
			item = item->next;			
			data->halfbodyrResource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictMonster* DictMonsterManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictMonster* data = (DictMonster*)(data_list.at(key));
	return data;
}
DictMonsterManager* DictMonsterManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictMonsterManager();
	}
	return _instance;
}
Vector<DictMonster*>* DictMonsterManager::getDataList()
{
	Vector<DictMonster*>* list = new Vector<DictMonster*>();
	for(auto value : data_list)
	{
		DictMonster* data  = ( DictMonster* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictMonsterManager::~DictMonsterManager()
{
	destroyInstance();
}
void DictMonsterManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
