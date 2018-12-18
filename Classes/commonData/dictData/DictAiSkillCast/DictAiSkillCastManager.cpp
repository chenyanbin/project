#include "DictAiSkillCastManager.h"
#include "../../../common/PublicShowUI.h"

DictAiSkillCastManager* DictAiSkillCastManager::_instance = NULL;
void DictAiSkillCastManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictAiSkillCast* data = new DictAiSkillCast();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->waitTimeId = item->valueInt;
			item = item->next;			
			data->WaitPerformance = item->valueInt;
			item = item->next;			
			data->s1Rate = item->valueInt;
			item = item->next;			
			data->s1Range = item->valueInt;
			item = item->next;			
			data->s6Rate = item->valueInt;
			item = item->next;			
			data->s6Range = item->valueInt;
			item = item->next;			
			data->s7Rate = item->valueInt;
			item = item->next;			
			data->s7Range = item->valueInt;
			item = item->next;			
			data->s8Rate = item->valueInt;
			item = item->next;			
			data->s8Range = item->valueInt;
			item = item->next;			
			data->s9Rate = item->valueInt;
			item = item->next;			
			data->s9Range = item->valueInt;
			item = item->next;			
			data->s10Rate = item->valueInt;
			item = item->next;			
			data->s10Range = item->valueInt;
			item = item->next;			
			data->s11Rate = item->valueInt;
			item = item->next;			
			data->s11Range = item->valueInt;
			item = item->next;			
			data->firstSkill = item->valueInt;
			item = item->next;			
			data->fWaitTime = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictAiSkillCast* DictAiSkillCastManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictAiSkillCast* data = (DictAiSkillCast*)(data_list.at(key));
	return data;
}
DictAiSkillCastManager* DictAiSkillCastManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictAiSkillCastManager();
	}
	return _instance;
}
Vector<DictAiSkillCast*>* DictAiSkillCastManager::getDataList()
{
	Vector<DictAiSkillCast*>* list = new Vector<DictAiSkillCast*>();
	for(auto value : data_list)
	{
		DictAiSkillCast* data  = ( DictAiSkillCast* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictAiSkillCastManager::~DictAiSkillCastManager()
{
	destroyInstance();
}
void DictAiSkillCastManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
