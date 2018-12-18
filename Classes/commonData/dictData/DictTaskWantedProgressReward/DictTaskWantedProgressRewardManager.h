#ifndef __DictTaskWantedProgressRewardManager__
#define __DictTaskWantedProgressRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskWantedProgressReward.h"
#include "editor-support/spine/Json.h"
class DictTaskWantedProgressRewardManager
{ 
public:
	~DictTaskWantedProgressRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskWantedProgressRewardManager* getInstance();
	DictTaskWantedProgressReward* getData(int id);
	Vector<DictTaskWantedProgressReward*>* getDataList();
private:
	static DictTaskWantedProgressRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskWantedProgressRewardManager(){};
};
#endif
