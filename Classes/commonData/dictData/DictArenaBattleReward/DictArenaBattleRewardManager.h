#ifndef __DictArenaBattleRewardManager__
#define __DictArenaBattleRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaBattleReward.h"
#include "editor-support/spine/Json.h"
class DictArenaBattleRewardManager
{ 
public:
	~DictArenaBattleRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaBattleRewardManager* getInstance();
	DictArenaBattleReward* getData(int id);
	Vector<DictArenaBattleReward*>* getDataList();
private:
	static DictArenaBattleRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaBattleRewardManager(){};
};
#endif
