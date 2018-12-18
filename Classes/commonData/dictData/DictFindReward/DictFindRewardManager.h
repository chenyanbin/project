#ifndef __DictFindRewardManager__
#define __DictFindRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFindReward.h"
#include "editor-support/spine/Json.h"
class DictFindRewardManager
{ 
public:
	~DictFindRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFindRewardManager* getInstance();
	DictFindReward* getData(int id);
	Vector<DictFindReward*>* getDataList();
private:
	static DictFindRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFindRewardManager(){};
};
#endif
