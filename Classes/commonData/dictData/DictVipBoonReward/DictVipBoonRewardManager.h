#ifndef __DictVipBoonRewardManager__
#define __DictVipBoonRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictVipBoonReward.h"
#include "editor-support/spine/Json.h"
class DictVipBoonRewardManager
{ 
public:
	~DictVipBoonRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictVipBoonRewardManager* getInstance();
	DictVipBoonReward* getData(int id);
	Vector<DictVipBoonReward*>* getDataList();
private:
	static DictVipBoonRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictVipBoonRewardManager(){};
};
#endif
