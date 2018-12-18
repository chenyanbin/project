#ifndef __DictStartRoleManager__
#define __DictStartRoleManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStartRole.h"
#include "editor-support/spine/Json.h"
class DictStartRoleManager
{ 
public:
	~DictStartRoleManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStartRoleManager* getInstance();
	DictStartRole* getData(int id);
	Vector<DictStartRole*>* getDataList();
private:
	static DictStartRoleManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStartRoleManager(){};
};
#endif
