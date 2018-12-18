#include "DictGlobalFormulaManager.h"
#include "../../../common/PublicShowUI.h"

DictGlobalFormulaManager* DictGlobalFormulaManager::_instance = NULL;
void DictGlobalFormulaManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictGlobalFormula* data = new DictGlobalFormula();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->type = item->valueString; 
			item = item->next;			
			data->usage = item->valueString; 
			item = item->next;			
			data->valueType = item->valueString; 
			item = item->next;			
			data->value = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictGlobalFormula* DictGlobalFormulaManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictGlobalFormula* data = (DictGlobalFormula*)(data_list.at(key));
	return data;
}
DictGlobalFormulaManager* DictGlobalFormulaManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictGlobalFormulaManager();
	}
	return _instance;
}
Vector<DictGlobalFormula*>* DictGlobalFormulaManager::getDataList()
{
	Vector<DictGlobalFormula*>* list = new Vector<DictGlobalFormula*>();
	for(auto value : data_list)
	{
		DictGlobalFormula* data  = ( DictGlobalFormula* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictGlobalFormulaManager::~DictGlobalFormulaManager()
{
	destroyInstance();
}
void DictGlobalFormulaManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
