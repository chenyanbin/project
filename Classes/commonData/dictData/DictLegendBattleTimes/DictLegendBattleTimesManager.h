#ifndef __DictLegendBattleTimesManager__
#define __DictLegendBattleTimesManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendBattleTimes.h"
#include "editor-support/spine/Json.h"
class DictLegendBattleTimesManager
{ 
public:
	~DictLegendBattleTimesManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendBattleTimesManager* getInstance();
	DictLegendBattleTimes* getData(int id);
	Vector<DictLegendBattleTimes*>* getDataList();
private:
	static DictLegendBattleTimesManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendBattleTimesManager(){};
};
#endif
