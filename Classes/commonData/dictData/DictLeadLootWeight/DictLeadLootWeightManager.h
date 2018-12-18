#ifndef __DictLeadLootWeightManager__
#define __DictLeadLootWeightManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLeadLootWeight.h"
#include "editor-support/spine/Json.h"
class DictLeadLootWeightManager
{ 
public:
	~DictLeadLootWeightManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLeadLootWeightManager* getInstance();
	DictLeadLootWeight* getData(int id);
	Vector<DictLeadLootWeight*>* getDataList();
private:
	static DictLeadLootWeightManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLeadLootWeightManager(){};
};
#endif
