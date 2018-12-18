#ifndef __DictWeekChargeRewardManager__
#define __DictWeekChargeRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekChargeReward.h"
#include "editor-support/spine/Json.h"
class DictWeekChargeRewardManager
{ 
public:
	~DictWeekChargeRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekChargeRewardManager* getInstance();
	DictWeekChargeReward* getData(int id);
	Vector<DictWeekChargeReward*>* getDataList();
private:
	static DictWeekChargeRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekChargeRewardManager(){};
};
#endif
