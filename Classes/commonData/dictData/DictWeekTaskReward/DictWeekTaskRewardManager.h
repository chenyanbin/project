#ifndef __DictWeekTaskRewardManager__
#define __DictWeekTaskRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekTaskReward.h"
#include "editor-support/spine/Json.h"
class DictWeekTaskRewardManager
{ 
public:
	~DictWeekTaskRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekTaskRewardManager* getInstance();
	DictWeekTaskReward* getData(int id);
	Vector<DictWeekTaskReward*>* getDataList();
private:
	static DictWeekTaskRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekTaskRewardManager(){};
};
#endif
