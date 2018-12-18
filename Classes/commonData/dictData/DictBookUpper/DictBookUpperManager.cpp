#include "DictBookUpperManager.h"
#include "../../../common/PublicShowUI.h"

DictBookUpperManager* DictBookUpperManager::_instance = NULL;
void DictBookUpperManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictBookUpper* data = new DictBookUpper();
			
			data->id = item->valueInt;
			item = item->next;			
			data->quality = item->valueInt;
			item = item->next;			
			data->friendUpper = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictBookUpper* DictBookUpperManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictBookUpper* data = (DictBookUpper*)(data_list.at(key));
	return data;
}
DictBookUpperManager* DictBookUpperManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictBookUpperManager();
	}
	return _instance;
}
Vector<DictBookUpper*>* DictBookUpperManager::getDataList()
{
	Vector<DictBookUpper*>* list = new Vector<DictBookUpper*>();
	for(auto value : data_list)
	{
		DictBookUpper* data  = ( DictBookUpper* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictBookUpperManager::~DictBookUpperManager()
{
	destroyInstance();
}
void DictBookUpperManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
