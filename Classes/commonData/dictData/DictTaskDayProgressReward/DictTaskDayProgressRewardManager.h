#ifndef __DictTaskDayProgressRewardManager__
#define __DictTaskDayProgressRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskDayProgressReward.h"
#include "editor-support/spine/Json.h"
class DictTaskDayProgressRewardManager
{ 
public:
	~DictTaskDayProgressRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskDayProgressRewardManager* getInstance();
	DictTaskDayProgressReward* getData(int id);
	Vector<DictTaskDayProgressReward*>* getDataList();
private:
	static DictTaskDayProgressRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskDayProgressRewardManager(){};
};
#endif
