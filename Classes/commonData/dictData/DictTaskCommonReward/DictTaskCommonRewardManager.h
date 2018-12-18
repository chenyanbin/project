#ifndef __DictTaskCommonRewardManager__
#define __DictTaskCommonRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskCommonReward.h"
#include "editor-support/spine/Json.h"
class DictTaskCommonRewardManager
{ 
public:
	~DictTaskCommonRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskCommonRewardManager* getInstance();
	DictTaskCommonReward* getData(int id);
	Vector<DictTaskCommonReward*>* getDataList();
private:
	static DictTaskCommonRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskCommonRewardManager(){};
};
#endif
