#ifndef __DictSignRewardManager__
#define __DictSignRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictSignReward.h"
#include "editor-support/spine/Json.h"
class DictSignRewardManager
{ 
public:
	~DictSignRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictSignRewardManager* getInstance();
	DictSignReward* getData(int id);
	Vector<DictSignReward*>* getDataList();
private:
	static DictSignRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictSignRewardManager(){};
};
#endif
