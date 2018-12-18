#ifndef __DictVipBoonWeekRewardManager__
#define __DictVipBoonWeekRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictVipBoonWeekReward.h"
#include "editor-support/spine/Json.h"
class DictVipBoonWeekRewardManager
{ 
public:
	~DictVipBoonWeekRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictVipBoonWeekRewardManager* getInstance();
	DictVipBoonWeekReward* getData(int id);
	Vector<DictVipBoonWeekReward*>* getDataList();
private:
	static DictVipBoonWeekRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictVipBoonWeekRewardManager(){};
};
#endif
