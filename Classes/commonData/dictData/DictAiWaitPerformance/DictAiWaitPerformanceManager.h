#ifndef __DictAiWaitPerformanceManager__
#define __DictAiWaitPerformanceManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictAiWaitPerformance.h"
#include "editor-support/spine/Json.h"
class DictAiWaitPerformanceManager
{ 
public:
	~DictAiWaitPerformanceManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictAiWaitPerformanceManager* getInstance();
	DictAiWaitPerformance* getData(int id);
	Vector<DictAiWaitPerformance*>* getDataList();
private:
	static DictAiWaitPerformanceManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictAiWaitPerformanceManager(){};
};
#endif
