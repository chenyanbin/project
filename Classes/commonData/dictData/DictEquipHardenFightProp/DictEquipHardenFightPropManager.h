#ifndef __DictEquipHardenFightPropManager__
#define __DictEquipHardenFightPropManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipHardenFightProp.h"
#include "editor-support/spine/Json.h"
class DictEquipHardenFightPropManager
{ 
public:
	~DictEquipHardenFightPropManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipHardenFightPropManager* getInstance();
	DictEquipHardenFightProp* getData(int id);
	Vector<DictEquipHardenFightProp*>* getDataList();
private:
	static DictEquipHardenFightPropManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipHardenFightPropManager(){};
};
#endif
