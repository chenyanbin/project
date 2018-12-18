#ifndef __DictCardCostManager__
#define __DictCardCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictCardCost.h"
#include "editor-support/spine/Json.h"
class DictCardCostManager
{ 
public:
	~DictCardCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictCardCostManager* getInstance();
	DictCardCost* getData(int id);
	Vector<DictCardCost*>* getDataList();
private:
	static DictCardCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictCardCostManager(){};
};
#endif
