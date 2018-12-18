#ifndef __DictLineupOpenCostManager__
#define __DictLineupOpenCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLineupOpenCost.h"
#include "editor-support/spine/Json.h"
class DictLineupOpenCostManager
{ 
public:
	~DictLineupOpenCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLineupOpenCostManager* getInstance();
	DictLineupOpenCost* getData(int id);
	Vector<DictLineupOpenCost*>* getDataList();
private:
	static DictLineupOpenCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLineupOpenCostManager(){};
};
#endif
