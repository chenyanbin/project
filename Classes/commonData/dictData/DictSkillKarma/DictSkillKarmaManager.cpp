#include "DictSkillKarmaManager.h"
#include "../../../common/PublicShowUI.h"

DictSkillKarmaManager* DictSkillKarmaManager::_instance = NULL;
void DictSkillKarmaManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictSkillKarma* data = new DictSkillKarma();
			
			data->skillId = item->valueInt;
			item = item->next;			
			data->heroName = item->valueString; 
			item = item->next;			
			data->heroId = item->valueInt;
			item = item->next;			
			data->karmaHeroName = item->valueString; 
			item = item->next;			
			data->karmaHeroId = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->skillId), data);
		}
		node = node->next;
	}
}
DictSkillKarma* DictSkillKarmaManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictSkillKarma* data = (DictSkillKarma*)(data_list.at(key));
	return data;
}
DictSkillKarmaManager* DictSkillKarmaManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictSkillKarmaManager();
	}
	return _instance;
}
Vector<DictSkillKarma*>* DictSkillKarmaManager::getDataList()
{
	Vector<DictSkillKarma*>* list = new Vector<DictSkillKarma*>();
	for(auto value : data_list)
	{
		DictSkillKarma* data  = ( DictSkillKarma* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictSkillKarmaManager::~DictSkillKarmaManager()
{
	destroyInstance();
}
void DictSkillKarmaManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
