#ifndef __DictMusouBattleRewardManager__
#define __DictMusouBattleRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMusouBattleReward.h"
#include "editor-support/spine/Json.h"
class DictMusouBattleRewardManager
{ 
public:
	~DictMusouBattleRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMusouBattleRewardManager* getInstance();
	DictMusouBattleReward* getData(int id);
	Vector<DictMusouBattleReward*>* getDataList();
private:
	static DictMusouBattleRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMusouBattleRewardManager(){};
};
#endif
