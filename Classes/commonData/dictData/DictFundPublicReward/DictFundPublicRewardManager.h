#ifndef __DictFundPublicRewardManager__
#define __DictFundPublicRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFundPublicReward.h"
#include "editor-support/spine/Json.h"
class DictFundPublicRewardManager
{ 
public:
	~DictFundPublicRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFundPublicRewardManager* getInstance();
	DictFundPublicReward* getData(int id);
	Vector<DictFundPublicReward*>* getDataList();
private:
	static DictFundPublicRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFundPublicRewardManager(){};
};
#endif
