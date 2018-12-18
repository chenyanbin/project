#ifndef __DictWeekCostRewardManager__
#define __DictWeekCostRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekCostReward.h"
#include "editor-support/spine/Json.h"
class DictWeekCostRewardManager
{ 
public:
	~DictWeekCostRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekCostRewardManager* getInstance();
	DictWeekCostReward* getData(int id);
	Vector<DictWeekCostReward*>* getDataList();
private:
	static DictWeekCostRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekCostRewardManager(){};
};
#endif
