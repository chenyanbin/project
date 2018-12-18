#include "DictHeroQualityUpManager.h"
#include "../../../common/PublicShowUI.h"

DictHeroQualityUpManager* DictHeroQualityUpManager::_instance = NULL;
void DictHeroQualityUpManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictHeroQualityUp* data = new DictHeroQualityUp();
			
			data->quality = item->valueInt;
			item = item->next;			
			data->qualityDesc = item->valueString; 
			item = item->next;			
			data->attack1Item1Id = item->valueInt;
			item = item->next;			
			data->attack2Item1Id = item->valueInt;
			item = item->next;			
			data->attack3Item1Id = item->valueInt;
			item = item->next;			
			data->attack4Item1Id = item->valueInt;
			item = item->next;			
			data->attack5Item1Id = item->valueInt;
			item = item->next;			
			data->attack6Item1Id = item->valueInt;
			item = item->next;			
			data->item1Number = item->valueInt;
			item = item->next;			
			data->item2Id = item->valueInt;
			item = item->next;			
			data->item2Number = item->valueInt;
			item = item->next;			
			data->item3Id = item->valueInt;
			item = item->next;			
			data->item3Number = item->valueInt;
			item = item->next;			
			data->item4Id = item->valueInt;
			item = item->next;			
			data->item4Number = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->quality), data);
		}
		node = node->next;
	}
}
DictHeroQualityUp* DictHeroQualityUpManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictHeroQualityUp* data = (DictHeroQualityUp*)(data_list.at(key));
	return data;
}
DictHeroQualityUpManager* DictHeroQualityUpManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictHeroQualityUpManager();
	}
	return _instance;
}
Vector<DictHeroQualityUp*>* DictHeroQualityUpManager::getDataList()
{
	Vector<DictHeroQualityUp*>* list = new Vector<DictHeroQualityUp*>();
	for(auto value : data_list)
	{
		DictHeroQualityUp* data  = ( DictHeroQualityUp* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictHeroQualityUpManager::~DictHeroQualityUpManager()
{
	destroyInstance();
}
void DictHeroQualityUpManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
