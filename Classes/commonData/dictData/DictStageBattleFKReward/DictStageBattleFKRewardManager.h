#ifndef __DictStageBattleFKRewardManager__
#define __DictStageBattleFKRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBattleFKReward.h"
#include "editor-support/spine/Json.h"
class DictStageBattleFKRewardManager
{ 
public:
	~DictStageBattleFKRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBattleFKRewardManager* getInstance();
	DictStageBattleFKReward* getData(int id);
	Vector<DictStageBattleFKReward*>* getDataList();
private:
	static DictStageBattleFKRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBattleFKRewardManager(){};
};
#endif
