#ifndef __DictLegendPrestigeLootManager__
#define __DictLegendPrestigeLootManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendPrestigeLoot.h"
#include "editor-support/spine/Json.h"
class DictLegendPrestigeLootManager
{ 
public:
	~DictLegendPrestigeLootManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendPrestigeLootManager* getInstance();
	DictLegendPrestigeLoot* getData(int id);
	Vector<DictLegendPrestigeLoot*>* getDataList();
private:
	static DictLegendPrestigeLootManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendPrestigeLootManager(){};
};
#endif
