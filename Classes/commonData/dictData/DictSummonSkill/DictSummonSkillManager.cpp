#include "DictSummonSkillManager.h"
#include "../../../common/PublicShowUI.h"

DictSummonSkillManager* DictSummonSkillManager::_instance = NULL;
void DictSummonSkillManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictSummonSkill* data = new DictSummonSkill();
			
			data->id = item->valueInt;
			item = item->next;			
			data->heroName = item->valueString; 
			item = item->next;			
			data->summonId1 = item->valueInt;
			item = item->next;			
			data->summonId1Number = item->valueInt;
			item = item->next;			
			data->summonId1Time = item->valueInt;
			item = item->next;			
			data->summonId2 = item->valueInt;
			item = item->next;			
			data->summonId2Number = item->valueInt;
			item = item->next;			
			data->summonId2Time = item->valueInt;
			item = item->next;			
			data->summonId3 = item->valueInt;
			item = item->next;			
			data->summonId3Number = item->valueInt;
			item = item->next;			
			data->summonId3Time = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictSummonSkill* DictSummonSkillManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictSummonSkill* data = (DictSummonSkill*)(data_list.at(key));
	return data;
}
DictSummonSkillManager* DictSummonSkillManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictSummonSkillManager();
	}
	return _instance;
}
Vector<DictSummonSkill*>* DictSummonSkillManager::getDataList()
{
	Vector<DictSummonSkill*>* list = new Vector<DictSummonSkill*>();
	for(auto value : data_list)
	{
		DictSummonSkill* data  = ( DictSummonSkill* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictSummonSkillManager::~DictSummonSkillManager()
{
	destroyInstance();
}
void DictSummonSkillManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
