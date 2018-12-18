#ifndef __DictLeadLootSlotsManager__
#define __DictLeadLootSlotsManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLeadLootSlots.h"
#include "editor-support/spine/Json.h"
class DictLeadLootSlotsManager
{ 
public:
	~DictLeadLootSlotsManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLeadLootSlotsManager* getInstance();
	DictLeadLootSlots* getData(int id);
	Vector<DictLeadLootSlots*>* getDataList();
private:
	static DictLeadLootSlotsManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLeadLootSlotsManager(){};
};
#endif
