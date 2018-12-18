#include "DictGemstoneMineManager.h"
#include "../../../common/PublicShowUI.h"

DictGemstoneMineManager* DictGemstoneMineManager::_instance = NULL;
void DictGemstoneMineManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictGemstoneMine* data = new DictGemstoneMine();
			
			data->id = item->valueInt;
			item = item->next;			
			data->times = item->valueInt;
			item = item->next;			
			data->copper = item->valueInt;
			item = item->next;			
			data->gold = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictGemstoneMine* DictGemstoneMineManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictGemstoneMine* data = (DictGemstoneMine*)(data_list.at(key));
	return data;
}
DictGemstoneMineManager* DictGemstoneMineManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictGemstoneMineManager();
	}
	return _instance;
}
Vector<DictGemstoneMine*>* DictGemstoneMineManager::getDataList()
{
	Vector<DictGemstoneMine*>* list = new Vector<DictGemstoneMine*>();
	for(auto value : data_list)
	{
		DictGemstoneMine* data  = ( DictGemstoneMine* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictGemstoneMineManager::~DictGemstoneMineManager()
{
	destroyInstance();
}
void DictGemstoneMineManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
