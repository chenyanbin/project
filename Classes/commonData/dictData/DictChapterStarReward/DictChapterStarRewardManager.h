#ifndef __DictChapterStarRewardManager__
#define __DictChapterStarRewardManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictChapterStarReward.h"
#include "editor-support/spine/Json.h"
class DictChapterStarRewardManager
{ 
public:
	~DictChapterStarRewardManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictChapterStarRewardManager* getInstance();
	DictChapterStarReward* getData(int id);
	Vector<DictChapterStarReward*>* getDataList();
private:
	static DictChapterStarRewardManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictChapterStarRewardManager(){};
};
#endif
