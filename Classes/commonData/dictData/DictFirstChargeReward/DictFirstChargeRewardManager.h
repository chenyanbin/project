#ifndef __DictFirstChargeRewardManager__
#define __DictFirstChargeRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFirstChargeReward.h"
#include "editor-support/spine/Json.h"
class DictFirstChargeRewardManager
{ 
public:
	~DictFirstChargeRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFirstChargeRewardManager* getInstance();
	DictFirstChargeReward* getData(int id);
	Vector<DictFirstChargeReward*>* getDataList();
private:
	static DictFirstChargeRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFirstChargeRewardManager(){};
};
#endif
