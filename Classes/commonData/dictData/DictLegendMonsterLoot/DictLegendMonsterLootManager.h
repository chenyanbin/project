#ifndef __DictLegendMonsterLootManager__
#define __DictLegendMonsterLootManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendMonsterLoot.h"
#include "editor-support/spine/Json.h"
class DictLegendMonsterLootManager
{ 
public:
	~DictLegendMonsterLootManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendMonsterLootManager* getInstance();
	DictLegendMonsterLoot* getData(int id);
	Vector<DictLegendMonsterLoot*>* getDataList();
private:
	static DictLegendMonsterLootManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendMonsterLootManager(){};
};
#endif
