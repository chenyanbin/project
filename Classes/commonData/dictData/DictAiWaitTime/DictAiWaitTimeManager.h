#ifndef __DictAiWaitTimeManager__
#define __DictAiWaitTimeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictAiWaitTime.h"
#include "editor-support/spine/Json.h"
class DictAiWaitTimeManager
{ 
public:
	~DictAiWaitTimeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictAiWaitTimeManager* getInstance();
	DictAiWaitTime* getData(int id);
	Vector<DictAiWaitTime*>* getDataList();
private:
	static DictAiWaitTimeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictAiWaitTimeManager(){};
};
#endif
