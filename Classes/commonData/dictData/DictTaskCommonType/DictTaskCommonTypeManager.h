#ifndef __DictTaskCommonTypeManager__
#define __DictTaskCommonTypeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskCommonType.h"
#include "editor-support/spine/Json.h"
class DictTaskCommonTypeManager
{ 
public:
	~DictTaskCommonTypeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskCommonTypeManager* getInstance();
	DictTaskCommonType* getData(int id);
	Vector<DictTaskCommonType*>* getDataList();
private:
	static DictTaskCommonTypeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskCommonTypeManager(){};
};
#endif
