#include "DictChapterManager.h"
#include "../../../common/PublicShowUI.h"

DictChapterManager* DictChapterManager::_instance = NULL;
void DictChapterManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictChapter* data = new DictChapter();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->indexOrder = item->valueInt;
			item = item->next;			
			data->resourceBg = item->valueString; 
			item = item->next;			
			data->resourceFront = item->valueString; 
			item = item->next;			
			data->resourceSky = item->valueString; 
			item = item->next;			
			data->bossId = item->valueInt;
			item = item->next;			
			data->levelOpen = item->valueInt;
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictChapter* DictChapterManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictChapter* data = (DictChapter*)(data_list.at(key));
	return data;
}
DictChapterManager* DictChapterManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictChapterManager();
	}
	return _instance;
}
Vector<DictChapter*>* DictChapterManager::getDataList()
{
	Vector<DictChapter*>* list = new Vector<DictChapter*>();
	for(auto value : data_list)
	{
		DictChapter* data  = ( DictChapter* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictChapterManager::~DictChapterManager()
{
	destroyInstance();
}
void DictChapterManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
