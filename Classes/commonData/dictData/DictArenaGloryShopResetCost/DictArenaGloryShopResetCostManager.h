#ifndef __DictArenaGloryShopResetCostManager__
#define __DictArenaGloryShopResetCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaGloryShopResetCost.h"
#include "editor-support/spine/Json.h"
class DictArenaGloryShopResetCostManager
{ 
public:
	~DictArenaGloryShopResetCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaGloryShopResetCostManager* getInstance();
	DictArenaGloryShopResetCost* getData(int id);
	Vector<DictArenaGloryShopResetCost*>* getDataList();
private:
	static DictArenaGloryShopResetCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaGloryShopResetCostManager(){};
};
#endif
