#ifndef __DictBattlePotionCostManager__
#define __DictBattlePotionCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBattlePotionCost.h"
#include "editor-support/spine/Json.h"
class DictBattlePotionCostManager
{ 
public:
	~DictBattlePotionCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBattlePotionCostManager* getInstance();
	DictBattlePotionCost* getData(int id);
	Vector<DictBattlePotionCost*>* getDataList();
private:
	static DictBattlePotionCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBattlePotionCostManager(){};
};
#endif
