#include "DictHeroManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroManager* DictHeroManager::_instance = NULL;
void DictHeroManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHero* data = new DictHero();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->sex = item->valueInt;
			item = item->next;			
			data->force = item->valueInt;
			item = item->next;			
			data->attackType = item->valueInt;
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
			data->skill11 = item->valueInt;
			item = item->next;			
			data->skill7 = item->valueInt;
			item = item->next;			
			data->skill8 = item->valueInt;
			item = item->next;			
			data->skill9 = item->valueInt;
			item = item->next;			
			data->skill10 = item->valueInt;
			item = item->next;			
			data->skill12 = item->valueInt;
			item = item->next;			
			data->moveSpeed = item->valueInt;
			item = item->next;			
			data->sight = item->valueInt;
			item = item->next;			
			data->karma1 = item->valueInt;
			item = item->next;			
			data->karma2 = item->valueInt;
			item = item->next;			
			data->seq = item->valueInt;
			item = item->next;			
			data->initialStar = item->valueInt;
			item = item->next;			
			data->fireCoin = item->valueInt;
			item = item->next;			
			data->resource = item->valueString; 
			item = item->next;			
			data->resourceHighShifting = item->valueInt;
			item = item->next;			
			data->resourceShifting = item->valueInt;
			item = item->next;			
			data->resourceRun = item->valueString; 
			item = item->next;			
			data->dieVoice = item->valueString; 
			item = item->next;			
			data->aiId = item->valueInt;
			item = item->next;			
			data->delayTime = item->valueInt;
			item = item->next;			
			data->ssTime = item->valueInt;
			item = item->next;			
			data->attackEvaluate = item->valueInt;
			item = item->next;			
			data->defenseEvaluate = item->valueInt;
			item = item->next;			
			data->techniquesEvaluate = item->valueInt;
			item = item->next;			
			data->halfbodyrResource = item->valueString; 
			item = item->next;			
			data->headResource = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictHero* DictHeroManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHero* data = (DictHero*)(data_list.at(key));
	return data;
}
DictHeroManager* DictHeroManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroManager();
	}
	return _instance;
}
Vector<DictHero*>* DictHeroManager::getDataList()
{
	Vector<DictHero*>* list = new Vector<DictHero*>();
	for(auto value : data_list)
	{
		DictHero* data  = ( DictHero* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroManager::~DictHeroManager()
{
	destroyInstance();
}
void DictHeroManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
