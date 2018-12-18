#include "DictSkillManager.h"
#include "../../../common/PublicShowUI.h"

DictSkillManager* DictSkillManager::_instance = NULL;
void DictSkillManager::setConfigData(Json* json)
{
	Json* node = json->child;
	node = node->next;
	while (node)
	{
		if(node->type == Json_Array)
		{
			Json* item = node->child;
			DictSkill* data = new DictSkill();
			
			data->id = item->valueInt;
			item = item->next;			
			data->name = item->valueString; 
			item = item->next;			
			data->ename = item->valueString; 
			item = item->next;			
			data->desc = item->valueString; 
			item = item->next;			
			data->type = item->valueInt;
			item = item->next;			
			data->attackType = item->valueInt;
			item = item->next;			
			data->costWay = item->valueInt;
			item = item->next;			
			data->coldDowm = item->valueInt;
			item = item->next;			
			data->costRage = item->valueInt;
			item = item->next;			
			data->target = item->valueInt;
			item = item->next;			
			data->knockDown = item->valueInt;
			item = item->next;			
			data->knockFly = item->valueInt;
			item = item->next;			
			data->actionHurt = item->valueInt;
			item = item->next;			
			data->flashMove = item->valueInt;
			item = item->next;			
			data->beatBack = item->valueInt;
			item = item->next;			
			data->hurtBackward = item->valueInt;
			item = item->next;			
			data->hurtForward = item->valueInt;
			item = item->next;			
			data->hurtHigh = item->valueInt;
			item = item->next;			
			data->hurtEffectTimes = item->valueInt;
			item = item->next;			
			data->heroShiftBackward = item->valueInt;
			item = item->next;			
			data->heroShiftForward = item->valueInt;
			item = item->next;			
			data->moveTime = item->valueFloat;
			item = item->next;			
			data->effectBlastBackward = item->valueInt;
			item = item->next;			
			data->effectBlastForward = item->valueInt;
			item = item->next;			
			data->effectPositionBackward = item->valueInt;
			item = item->next;			
			data->effectPositionForward = item->valueInt;
			item = item->next;			
			data->effectRangeBackward = item->valueInt;
			item = item->next;			
			data->effectRangeForward = item->valueInt;
			item = item->next;			
			data->resourceHighShifting = item->valueInt;
			item = item->next;			
			data->nameResource = item->valueString; 
			item = item->next;			
			data->flyResource = item->valueString; 
			item = item->next;			
			data->flyResourceTime = item->valueFloat;
			item = item->next;			
			data->flyRLoopMarker = item->valueInt;
			item = item->next;			
			data->hitResource = item->valueString; 
			item = item->next;			
			data->hitHighShifting = item->valueInt;
			item = item->next;			
			data->fullScreen = item->valueString; 
			item = item->next;			
			data->icon = item->valueString; 
			item = item->next;			
			data->damagePower1 = item->valueInt;
			item = item->next;			
			data->damagePower2 = item->valueInt;
			item = item->next;			
			data->isTurn = item->valueInt;
			item = item->next;			
			data->damageNumber = item->valueInt;
			item = item->next;			
			data->toBuffId = item->valueString; 
			item = item->next;			
			data->buffOdds = item->valueInt;
			item = item->next;			
			data->soundUse = item->valueString; 
			item = item->next;			
			data->soundFly = item->valueString; 
			item = item->next;			
			data->soundHit = item->valueString; 
			item = item->next;			
			data->colorHit = item->valueString; 
		data_list.insert(PublicShowUI::numberToString(data->id), data);
		}
		node = node->next;
	}
}
DictSkill* DictSkillManager::getData(int id)
{
	string key = PublicShowUI::numberToString(id);
	DictSkill* data = (DictSkill*)(data_list.at(key));
	return data;
}
DictSkillManager* DictSkillManager::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new DictSkillManager();
	}
	return _instance;
}
Vector<DictSkill*>* DictSkillManager::getDataList()
{
	Vector<DictSkill*>* list = new Vector<DictSkill*>();
	for(auto value : data_list)
	{
		DictSkill* data  = ( DictSkill* )value.second;
		list->pushBack(data);		
	}
	return list;
}
DictSkillManager::~DictSkillManager()
{
	destroyInstance();
}
void DictSkillManager::destroyInstance()
{
	if(_instance)
	{
		data_list.clear();
		delete _instance;
		_instance = NULL;
	}
}
