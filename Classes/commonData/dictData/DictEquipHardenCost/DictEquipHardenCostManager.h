#ifndef __DictEquipHardenCostManager__
#define __DictEquipHardenCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipHardenCost.h"
#include "editor-support/spine/Json.h"
class DictEquipHardenCostManager
{ 
public:
	~DictEquipHardenCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipHardenCostManager* getInstance();
	DictEquipHardenCost* getData(int id);
	Vector<DictEquipHardenCost*>* getDataList();
private:
	static DictEquipHardenCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipHardenCostManager(){};
};
#endif
