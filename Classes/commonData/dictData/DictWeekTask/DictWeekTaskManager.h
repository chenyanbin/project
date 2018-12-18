#ifndef __DictWeekTaskManager__
#define __DictWeekTaskManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekTask.h"
#include "editor-support/spine/Json.h"
class DictWeekTaskManager
{ 
public:
	~DictWeekTaskManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekTaskManager* getInstance();
	DictWeekTask* getData(int id);
	Vector<DictWeekTask*>* getDataList();
private:
	static DictWeekTaskManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekTaskManager(){};
};
#endif
