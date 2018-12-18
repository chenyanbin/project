#ifndef __DictChargeCostManager__
#define __DictChargeCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictChargeCost.h"
#include "editor-support/spine/Json.h"
class DictChargeCostManager
{ 
public:
	~DictChargeCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictChargeCostManager* getInstance();
	DictChargeCost* getData(int id);
	Vector<DictChargeCost*>* getDataList();
private:
	static DictChargeCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictChargeCostManager(){};
};
#endif
