#ifndef __DictArenaRankWeeksRewardManager__
#define __DictArenaRankWeeksRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaRankWeeksReward.h"
#include "editor-support/spine/Json.h"
class DictArenaRankWeeksRewardManager
{ 
public:
	~DictArenaRankWeeksRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaRankWeeksRewardManager* getInstance();
	DictArenaRankWeeksReward* getData(int id);
	Vector<DictArenaRankWeeksReward*>* getDataList();
private:
	static DictArenaRankWeeksRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaRankWeeksRewardManager(){};
};
#endif
