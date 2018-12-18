#ifndef __DictWeekShopRewardManager__
#define __DictWeekShopRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekShopReward.h"
#include "editor-support/spine/Json.h"
class DictWeekShopRewardManager
{ 
public:
	~DictWeekShopRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekShopRewardManager* getInstance();
	DictWeekShopReward* getData(int id);
	Vector<DictWeekShopReward*>* getDataList();
private:
	static DictWeekShopRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekShopRewardManager(){};
};
#endif
