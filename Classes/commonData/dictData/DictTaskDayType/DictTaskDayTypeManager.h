#ifndef __DictTaskDayTypeManager__
#define __DictTaskDayTypeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskDayType.h"
#include "editor-support/spine/Json.h"
class DictTaskDayTypeManager
{ 
public:
	~DictTaskDayTypeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskDayTypeManager* getInstance();
	DictTaskDayType* getData(int id);
	Vector<DictTaskDayType*>* getDataList();
private:
	static DictTaskDayTypeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskDayTypeManager(){};
};
#endif
