#ifndef __DictStageBattleRewardManager__
#define __DictStageBattleRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBattleReward.h"
#include "editor-support/spine/Json.h"
class DictStageBattleRewardManager
{ 
public:
	~DictStageBattleRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBattleRewardManager* getInstance();
	DictStageBattleReward* getData(int id);
	Vector<DictStageBattleReward*>* getDataList();
private:
	static DictStageBattleRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBattleRewardManager(){};
};
#endif
