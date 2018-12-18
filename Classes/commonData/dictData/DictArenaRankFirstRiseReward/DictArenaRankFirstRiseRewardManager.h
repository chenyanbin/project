#ifndef __DictArenaRankFirstRiseRewardManager__
#define __DictArenaRankFirstRiseRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaRankFirstRiseReward.h"
#include "editor-support/spine/Json.h"
class DictArenaRankFirstRiseRewardManager
{ 
public:
	~DictArenaRankFirstRiseRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaRankFirstRiseRewardManager* getInstance();
	DictArenaRankFirstRiseReward* getData(int id);
	Vector<DictArenaRankFirstRiseReward*>* getDataList();
private:
	static DictArenaRankFirstRiseRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaRankFirstRiseRewardManager(){};
};
#endif
