#ifndef __DictLeadLootPoolManager__
#define __DictLeadLootPoolManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLeadLootPool.h"
#include "editor-support/spine/Json.h"
class DictLeadLootPoolManager
{ 
public:
	~DictLeadLootPoolManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLeadLootPoolManager* getInstance();
	DictLeadLootPool* getData(int id);
	Vector<DictLeadLootPool*>* getDataList();
private:
	static DictLeadLootPoolManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLeadLootPoolManager(){};
};
#endif
