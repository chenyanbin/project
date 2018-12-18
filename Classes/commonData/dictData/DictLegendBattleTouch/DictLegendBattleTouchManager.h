#ifndef __DictLegendBattleTouchManager__
#define __DictLegendBattleTouchManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendBattleTouch.h"
#include "editor-support/spine/Json.h"
class DictLegendBattleTouchManager
{ 
public:
	~DictLegendBattleTouchManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendBattleTouchManager* getInstance();
	DictLegendBattleTouch* getData(int id);
	Vector<DictLegendBattleTouch*>* getDataList();
private:
	static DictLegendBattleTouchManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendBattleTouchManager(){};
};
#endif
