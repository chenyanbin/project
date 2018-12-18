#ifndef __DictTaskDayRewardManager__
#define __DictTaskDayRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskDayReward.h"
#include "editor-support/spine/Json.h"
class DictTaskDayRewardManager
{ 
public:
	~DictTaskDayRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskDayRewardManager* getInstance();
	DictTaskDayReward* getData(int id);
	Vector<DictTaskDayReward*>* getDataList();
private:
	static DictTaskDayRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskDayRewardManager(){};
};
#endif
