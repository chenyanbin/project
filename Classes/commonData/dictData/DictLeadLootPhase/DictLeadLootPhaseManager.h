#ifndef __DictLeadLootPhaseManager__
#define __DictLeadLootPhaseManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLeadLootPhase.h"
#include "editor-support/spine/Json.h"
class DictLeadLootPhaseManager
{ 
public:
	~DictLeadLootPhaseManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLeadLootPhaseManager* getInstance();
	DictLeadLootPhase* getData(int id);
	Vector<DictLeadLootPhase*>* getDataList();
private:
	static DictLeadLootPhaseManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLeadLootPhaseManager(){};
};
#endif
