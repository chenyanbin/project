#ifndef __DictStageStarRewardManager__
#define __DictStageStarRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageStarReward.h"
#include "editor-support/spine/Json.h"
class DictStageStarRewardManager
{ 
public:
	~DictStageStarRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageStarRewardManager* getInstance();
	DictStageStarReward* getData(int id);
	Vector<DictStageStarReward*>* getDataList();
private:
	static DictStageStarRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageStarRewardManager(){};
};
#endif
