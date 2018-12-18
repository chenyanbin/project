#ifndef __DictVipGiftCostManager__
#define __DictVipGiftCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictVipGiftCost.h"
#include "editor-support/spine/Json.h"
class DictVipGiftCostManager
{ 
public:
	~DictVipGiftCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictVipGiftCostManager* getInstance();
	DictVipGiftCost* getData(int id);
	Vector<DictVipGiftCost*>* getDataList();
private:
	static DictVipGiftCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictVipGiftCostManager(){};
};
#endif
