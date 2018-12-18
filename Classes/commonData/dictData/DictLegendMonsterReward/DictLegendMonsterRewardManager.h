#ifndef __DictLegendMonsterRewardManager__
#define __DictLegendMonsterRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendMonsterReward.h"
#include "editor-support/spine/Json.h"
class DictLegendMonsterRewardManager
{ 
public:
	~DictLegendMonsterRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendMonsterRewardManager* getInstance();
	DictLegendMonsterReward* getData(int id);
	Vector<DictLegendMonsterReward*>* getDataList();
private:
	static DictLegendMonsterRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendMonsterRewardManager(){};
};
#endif
