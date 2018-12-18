#ifndef __DictWeekLoginRewardManager__
#define __DictWeekLoginRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWeekLoginReward.h"
#include "editor-support/spine/Json.h"
class DictWeekLoginRewardManager
{ 
public:
	~DictWeekLoginRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWeekLoginRewardManager* getInstance();
	DictWeekLoginReward* getData(int id);
	Vector<DictWeekLoginReward*>* getDataList();
private:
	static DictWeekLoginRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWeekLoginRewardManager(){};
};
#endif
