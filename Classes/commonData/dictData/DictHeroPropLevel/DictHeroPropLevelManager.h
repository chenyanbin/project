#ifndef __DictHeroPropLevelManager__
#define __DictHeroPropLevelManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroPropLevel.h"
#include "editor-support/spine/Json.h"
class DictHeroPropLevelManager
{ 
public:
	~DictHeroPropLevelManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroPropLevelManager* getInstance();
	DictHeroPropLevel* getData(int id);
	Vector<DictHeroPropLevel*>* getDataList();
private:
	static DictHeroPropLevelManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroPropLevelManager(){};
};
#endif
