#ifndef __DictBookCostManager__
#define __DictBookCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBookCost.h"
#include "editor-support/spine/Json.h"
class DictBookCostManager
{ 
public:
	~DictBookCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBookCostManager* getInstance();
	DictBookCost* getData(int id);
	Vector<DictBookCost*>* getDataList();
private:
	static DictBookCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBookCostManager(){};
};
#endif
