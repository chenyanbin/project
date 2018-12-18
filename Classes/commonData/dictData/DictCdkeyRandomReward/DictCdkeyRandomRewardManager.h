#ifndef __DictCdkeyRandomRewardManager__
#define __DictCdkeyRandomRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictCdkeyRandomReward.h"
#include "editor-support/spine/Json.h"
class DictCdkeyRandomRewardManager
{ 
public:
	~DictCdkeyRandomRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictCdkeyRandomRewardManager* getInstance();
	DictCdkeyRandomReward* getData(int id);
	Vector<DictCdkeyRandomReward*>* getDataList();
private:
	static DictCdkeyRandomRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictCdkeyRandomRewardManager(){};
};
#endif
