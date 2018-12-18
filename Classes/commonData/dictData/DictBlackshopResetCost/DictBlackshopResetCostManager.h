#ifndef __DictBlackshopResetCostManager__
#define __DictBlackshopResetCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBlackshopResetCost.h"
#include "editor-support/spine/Json.h"
class DictBlackshopResetCostManager
{ 
public:
	~DictBlackshopResetCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBlackshopResetCostManager* getInstance();
	DictBlackshopResetCost* getData(int id);
	Vector<DictBlackshopResetCost*>* getDataList();
private:
	static DictBlackshopResetCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBlackshopResetCostManager(){};
};
#endif
