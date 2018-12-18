#ifndef __DictCdkeyRewardManager__
#define __DictCdkeyRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictCdkeyReward.h"
#include "editor-support/spine/Json.h"
class DictCdkeyRewardManager
{ 
public:
	~DictCdkeyRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictCdkeyRewardManager* getInstance();
	DictCdkeyReward* getData(int id);
	Vector<DictCdkeyReward*>* getDataList();
private:
	static DictCdkeyRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictCdkeyRewardManager(){};
};
#endif
