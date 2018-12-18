#include "DictStoryManager.h"
#include "../../../common/PublicShowUI.h"

DictStoryManager* DictStoryManager::_instance = NULL;
void DictStoryManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictStory* data = new DictStory();
			
			data->id = item->valueInt;
			item = item->next;			
			data->triggerType = item->valueInt;
			item = item->next;			
			data->triggerId = item->valueInt;
			item = item->next;			
			data->triggerNode = item->valueInt;
			item = item->next;			
			data->speakerType = item->valueInt;
			item = item->next;			
			data->speakerId = item->valueInt;
			item = item->next;			
			data->speakerPosition = item->valueInt;
			item = item->next;			
			data->speakerName = item->valueString; 
			item = item->next;			
			data->text = item->valueString; 
			item = item->next;			
			data->order = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictStory* DictStoryManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictStory* data = (DictStory*)(data_list.at(key));
	return data;
}
DictStoryManager* DictStoryManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictStoryManager();
	}
	return _instance;
}
Vector<DictStory*>* DictStoryManager::getDataList()
{
	Vector<DictStory*>* list = new Vector<DictStory*>();
	for(auto value : data_list)
	{
		DictStory* data  = ( DictStory* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictStoryManager::~DictStoryManager()
{
	destroyInstance();
}
void DictStoryManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
