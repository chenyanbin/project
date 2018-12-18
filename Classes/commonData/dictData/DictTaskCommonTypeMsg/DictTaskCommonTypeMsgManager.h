#ifndef __DictTaskCommonTypeMsgManager__
#define __DictTaskCommonTypeMsgManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskCommonTypeMsg.h"
#include "editor-support/spine/Json.h"
class DictTaskCommonTypeMsgManager
{ 
public:
	~DictTaskCommonTypeMsgManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskCommonTypeMsgManager* getInstance();
	DictTaskCommonTypeMsg* getData(int id);
	Vector<DictTaskCommonTypeMsg*>* getDataList();
private:
	static DictTaskCommonTypeMsgManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskCommonTypeMsgManager(){};
};
#endif
