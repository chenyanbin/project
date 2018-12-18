#include "DictTipsManager.h"
#include "../../../common/PublicShowUI.h"

DictTipsManager* DictTipsManager::_instance = NULL;
void DictTipsManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictTips* data = new DictTips();
			
			data->id = item->valueInt;
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->chRgb = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictTips* DictTipsManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictTips* data = (DictTips*)(data_list.at(key));
	return data;
}
DictTipsManager* DictTipsManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictTipsManager();
	}
	return _instance;
}
Vector<DictTips*>* DictTipsManager::getDataList()
{
	Vector<DictTips*>* list = new Vector<DictTips*>();
	for(auto value : data_list)
	{
		DictTips* data  = ( DictTips* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictTipsManager::~DictTipsManager()
{
	destroyInstance();
}
void DictTipsManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
