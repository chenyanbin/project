#ifndef __DictLegendDamageRewardManager__
#define __DictLegendDamageRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendDamageReward.h"
#include "editor-support/spine/Json.h"
class DictLegendDamageRewardManager
{ 
public:
	~DictLegendDamageRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendDamageRewardManager* getInstance();
	DictLegendDamageReward* getData(int id);
	Vector<DictLegendDamageReward*>* getDataList();
private:
	static DictLegendDamageRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendDamageRewardManager(){};
};
#endif
