#ifndef __DictSignEliteRewardManager__
#define __DictSignEliteRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictSignEliteReward.h"
#include "editor-support/spine/Json.h"
class DictSignEliteRewardManager
{ 
public:
	~DictSignEliteRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictSignEliteRewardManager* getInstance();
	DictSignEliteReward* getData(int id);
	Vector<DictSignEliteReward*>* getDataList();
private:
	static DictSignEliteRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictSignEliteRewardManager(){};
};
#endif
