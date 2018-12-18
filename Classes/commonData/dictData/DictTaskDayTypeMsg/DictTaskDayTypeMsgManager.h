#ifndef __DictTaskDayTypeMsgManager__
#define __DictTaskDayTypeMsgManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskDayTypeMsg.h"
#include "editor-support/spine/Json.h"
class DictTaskDayTypeMsgManager
{ 
public:
	~DictTaskDayTypeMsgManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskDayTypeMsgManager* getInstance();
	DictTaskDayTypeMsg* getData(int id);
	Vector<DictTaskDayTypeMsg*>* getDataList();
private:
	static DictTaskDayTypeMsgManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskDayTypeMsgManager(){};
};
#endif
