#ifndef __DictWeekTagManager__
#define __DictWeekTagManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekTag.h"
#include "editor-support/spine/Json.h"
class DictWeekTagManager
{ 
public:
	~DictWeekTagManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekTagManager* getInstance();
	DictWeekTag* getData(int id);
	Vector<DictWeekTag*>* getDataList();
private:
	static DictWeekTagManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekTagManager(){};
};
#endif
