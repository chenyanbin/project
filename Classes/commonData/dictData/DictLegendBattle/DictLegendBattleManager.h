#ifndef __DictLegendBattleManager__
#define __DictLegendBattleManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendBattle.h"
#include "editor-support/spine/Json.h"
class DictLegendBattleManager
{ 
public:
	~DictLegendBattleManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendBattleManager* getInstance();
	DictLegendBattle* getData(int id);
	Vector<DictLegendBattle*>* getDataList();
private:
	static DictLegendBattleManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendBattleManager(){};
};
#endif
