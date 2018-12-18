#ifndef __DictMusouBattlePrestigeRewardManager__
#define __DictMusouBattlePrestigeRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMusouBattlePrestigeReward.h"
#include "editor-support/spine/Json.h"
class DictMusouBattlePrestigeRewardManager
{ 
public:
	~DictMusouBattlePrestigeRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMusouBattlePrestigeRewardManager* getInstance();
	DictMusouBattlePrestigeReward* getData(int id);
	Vector<DictMusouBattlePrestigeReward*>* getDataList();
private:
	static DictMusouBattlePrestigeRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMusouBattlePrestigeRewardManager(){};
};
#endif
