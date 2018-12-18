#ifndef __DictLuckyGoldTotalRewardManager__
#define __DictLuckyGoldTotalRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLuckyGoldTotalReward.h"
#include "editor-support/spine/Json.h"
class DictLuckyGoldTotalRewardManager
{ 
public:
	~DictLuckyGoldTotalRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLuckyGoldTotalRewardManager* getInstance();
	DictLuckyGoldTotalReward* getData(int id);
	Vector<DictLuckyGoldTotalReward*>* getDataList();
private:
	static DictLuckyGoldTotalRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLuckyGoldTotalRewardManager(){};
};
#endif
