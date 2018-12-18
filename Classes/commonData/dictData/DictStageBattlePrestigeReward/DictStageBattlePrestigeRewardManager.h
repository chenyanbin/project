#ifndef __DictStageBattlePrestigeRewardManager__
#define __DictStageBattlePrestigeRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBattlePrestigeReward.h"
#include "editor-support/spine/Json.h"
class DictStageBattlePrestigeRewardManager
{ 
public:
	~DictStageBattlePrestigeRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBattlePrestigeRewardManager* getInstance();
	DictStageBattlePrestigeReward* getData(int id);
	Vector<DictStageBattlePrestigeReward*>* getDataList();
private:
	static DictStageBattlePrestigeRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBattlePrestigeRewardManager(){};
};
#endif
