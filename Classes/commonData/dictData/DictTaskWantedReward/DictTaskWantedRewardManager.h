#ifndef __DictTaskWantedRewardManager__
#define __DictTaskWantedRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskWantedReward.h"
#include "editor-support/spine/Json.h"
class DictTaskWantedRewardManager
{ 
public:
	~DictTaskWantedRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskWantedRewardManager* getInstance();
	DictTaskWantedReward* getData(int id);
	Vector<DictTaskWantedReward*>* getDataList();
private:
	static DictTaskWantedRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskWantedRewardManager(){};
};
#endif
