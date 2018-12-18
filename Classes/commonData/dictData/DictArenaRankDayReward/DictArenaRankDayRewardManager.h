#ifndef __DictArenaRankDayRewardManager__
#define __DictArenaRankDayRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaRankDayReward.h"
#include "editor-support/spine/Json.h"
class DictArenaRankDayRewardManager
{ 
public:
	~DictArenaRankDayRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaRankDayRewardManager* getInstance();
	DictArenaRankDayReward* getData(int id);
	Vector<DictArenaRankDayReward*>* getDataList();
private:
	static DictArenaRankDayRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaRankDayRewardManager(){};
};
#endif
