#ifndef __DictBattleRebornCostManager__
#define __DictBattleRebornCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBattleRebornCost.h"
#include "editor-support/spine/Json.h"
class DictBattleRebornCostManager
{ 
public:
	~DictBattleRebornCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBattleRebornCostManager* getInstance();
	DictBattleRebornCost* getData(int id);
	Vector<DictBattleRebornCost*>* getDataList();
private:
	static DictBattleRebornCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBattleRebornCostManager(){};
};
#endif
