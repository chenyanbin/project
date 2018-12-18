#ifndef __DictStageBattleMonsterRewardManager__
#define __DictStageBattleMonsterRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBattleMonsterReward.h"
#include "editor-support/spine/Json.h"
class DictStageBattleMonsterRewardManager
{ 
public:
	~DictStageBattleMonsterRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBattleMonsterRewardManager* getInstance();
	DictStageBattleMonsterReward* getData(int id);
	Vector<DictStageBattleMonsterReward*>* getDataList();
private:
	static DictStageBattleMonsterRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBattleMonsterRewardManager(){};
};
#endif
