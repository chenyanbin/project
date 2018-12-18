#ifndef __DictMonsterPropLevelManager__
#define __DictMonsterPropLevelManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMonsterPropLevel.h"
#include "editor-support/spine/Json.h"
class DictMonsterPropLevelManager
{ 
public:
	~DictMonsterPropLevelManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMonsterPropLevelManager* getInstance();
	DictMonsterPropLevel* getData(int id);
	Vector<DictMonsterPropLevel*>* getDataList();
private:
	static DictMonsterPropLevelManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMonsterPropLevelManager(){};
};
#endif
