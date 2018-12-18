#ifndef __DictTaskDayManager__
#define __DictTaskDayManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskDay.h"
#include "editor-support/spine/Json.h"
class DictTaskDayManager
{ 
public:
	~DictTaskDayManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskDayManager* getInstance();
	DictTaskDay* getData(int id);
	Vector<DictTaskDay*>* getDataList();
private:
	static DictTaskDayManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskDayManager(){};
};
#endif
