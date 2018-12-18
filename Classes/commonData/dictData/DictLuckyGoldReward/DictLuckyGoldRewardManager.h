#ifndef __DictLuckyGoldRewardManager__
#define __DictLuckyGoldRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLuckyGoldReward.h"
#include "editor-support/spine/Json.h"
class DictLuckyGoldRewardManager
{ 
public:
	~DictLuckyGoldRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLuckyGoldRewardManager* getInstance();
	DictLuckyGoldReward* getData(int id);
	Vector<DictLuckyGoldReward*>* getDataList();
private:
	static DictLuckyGoldRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLuckyGoldRewardManager(){};
};
#endif
