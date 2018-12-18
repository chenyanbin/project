#include "DictArenaMatchingRuleManager.h"
#include "../../../common/PublicShowUI.h"

DictArenaMatchingRuleManager* DictArenaMatchingRuleManager::_instance = NULL;
void DictArenaMatchingRuleManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictArenaMatchingRule* data = new DictArenaMatchingRule();
			
			data->id = item->valueInt;
			item = item->next;			
			data->sectionMin = item->valueInt;
			item = item->next;			
			data->sectionMax = item->valueInt;
			item = item->next;			
			data->position1SectionMin = item->valueInt;
			item = item->next;			
			data->position1SectionMax = item->valueInt;
			item = item->next;			
			data->position2SectionMin = item->valueInt;
			item = item->next;			
			data->position2SectionMax = item->valueInt;
			item = item->next;			
			data->position3SectionMin = item->valueInt;
			item = item->next;			
			data->position3SectionMax = item->valueInt;
			item = item->next;			
			data->position4SectionMin = item->valueInt;
			item = item->next;			
			data->position4SectionMax = item->valueInt;
			item = item->next;			
			data->position5SectionMin = item->valueInt;
			item = item->next;			
			data->position5SectionMax = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictArenaMatchingRule* DictArenaMatchingRuleManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictArenaMatchingRule* data = (DictArenaMatchingRule*)(data_list.at(key));
	return data;
}
DictArenaMatchingRuleManager* DictArenaMatchingRuleManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictArenaMatchingRuleManager();
	}
	return _instance;
}
Vector<DictArenaMatchingRule*>* DictArenaMatchingRuleManager::getDataList()
{
	Vector<DictArenaMatchingRule*>* list = new Vector<DictArenaMatchingRule*>();
	for(auto value : data_list)
	{
		DictArenaMatchingRule* data  = ( DictArenaMatchingRule* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictArenaMatchingRuleManager::~DictArenaMatchingRuleManager()
{
	destroyInstance();
}
void DictArenaMatchingRuleManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
