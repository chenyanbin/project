#ifndef __DictEquipForgeCostManager__
#define __DictEquipForgeCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipForgeCost.h"
#include "editor-support/spine/Json.h"
class DictEquipForgeCostManager
{ 
public:
	~DictEquipForgeCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipForgeCostManager* getInstance();
	DictEquipForgeCost* getData(int id);
	Vector<DictEquipForgeCost*>* getDataList();
private:
	static DictEquipForgeCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipForgeCostManager(){};
};
#endif
