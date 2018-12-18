#ifndef __DictEquipHardenLevelManager__
#define __DictEquipHardenLevelManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipHardenLevel.h"
#include "editor-support/spine/Json.h"
class DictEquipHardenLevelManager
{ 
public:
	~DictEquipHardenLevelManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipHardenLevelManager* getInstance();
	DictEquipHardenLevel* getData(int id);
	Vector<DictEquipHardenLevel*>* getDataList();
private:
	static DictEquipHardenLevelManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipHardenLevelManager(){};
};
#endif
