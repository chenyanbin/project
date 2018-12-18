#ifndef __DictRoleLevelManager__
#define __DictRoleLevelManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictRoleLevel.h"
#include "editor-support/spine/Json.h"
class DictRoleLevelManager
{ 
public:
	~DictRoleLevelManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictRoleLevelManager* getInstance();
	DictRoleLevel* getData(int id);
	Vector<DictRoleLevel*>* getDataList();
private:
	static DictRoleLevelManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictRoleLevelManager(){};
};
#endif
