#ifndef __DictFundRewardManager__
#define __DictFundRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFundReward.h"
#include "editor-support/spine/Json.h"
class DictFundRewardManager
{ 
public:
	~DictFundRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFundRewardManager* getInstance();
	DictFundReward* getData(int id);
	Vector<DictFundReward*>* getDataList();
private:
	static DictFundRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFundRewardManager(){};
};
#endif
