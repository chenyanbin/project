#include "DictChannelManager.h"
#include "../../../common/PublicShowUI.h"

DictChannelManager* DictChannelManager::_instance = NULL;
void DictChannelManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictChannel* data = new DictChannel();
			
			data->id = item->valueInt;
			item = item->next;			
			data->channelID = item->valueString; 
			item = item->next;			
			data->channelName = item->valueString; 
			item = item->next;			
			data->url = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictChannel* DictChannelManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictChannel* data = (DictChannel*)(data_list.at(key));
	return data;
}
DictChannelManager* DictChannelManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictChannelManager();
	}
	return _instance;
}
Vector<DictChannel*>* DictChannelManager::getDataList()
{
	Vector<DictChannel*>* list = new Vector<DictChannel*>();
	for(auto value : data_list)
	{
		DictChannel* data  = ( DictChannel* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictChannelManager::~DictChannelManager()
{
	destroyInstance();
}
void DictChannelManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
