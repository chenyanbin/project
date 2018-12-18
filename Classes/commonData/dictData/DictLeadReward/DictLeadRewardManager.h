#ifndef __DictLeadRewardManager__
#define __DictLeadRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLeadReward.h"
#include "editor-support/spine/Json.h"
class DictLeadRewardManager
{ 
public:
	~DictLeadRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLeadRewardManager* getInstance();
	DictLeadReward* getData(int id);
	Vector<DictLeadReward*>* getDataList();
private:
	static DictLeadRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLeadRewardManager(){};
};
#endif
