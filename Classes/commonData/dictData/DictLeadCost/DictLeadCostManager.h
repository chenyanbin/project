#ifndef __DictLeadCostManager__
#define __DictLeadCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLeadCost.h"
#include "editor-support/spine/Json.h"
class DictLeadCostManager
{ 
public:
	~DictLeadCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLeadCostManager* getInstance();
	DictLeadCost* getData(int id);
	Vector<DictLeadCost*>* getDataList();
private:
	static DictLeadCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLeadCostManager(){};
};
#endif
