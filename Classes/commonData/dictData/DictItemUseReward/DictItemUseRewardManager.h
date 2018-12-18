#ifndef __DictItemUseRewardManager__
#define __DictItemUseRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItemUseReward.h"
#include "editor-support/spine/Json.h"
class DictItemUseRewardManager
{ 
public:
	~DictItemUseRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemUseRewardManager* getInstance();
	DictItemUseReward* getData(int id);
	Vector<DictItemUseReward*>* getDataList();
private:
	static DictItemUseRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemUseRewardManager(){};
};
#endif
