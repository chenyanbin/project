#ifndef __DictStageBuildingManager__
#define __DictStageBuildingManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBuilding.h"
#include "editor-support/spine/Json.h"
class DictStageBuildingManager
{ 
public:
	~DictStageBuildingManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBuildingManager* getInstance();
	DictStageBuilding* getData(int id);
	Vector<DictStageBuilding*>* getDataList();
private:
	static DictStageBuildingManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBuildingManager(){};
};
#endif
