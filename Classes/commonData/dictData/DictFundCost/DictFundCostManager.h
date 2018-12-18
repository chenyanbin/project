#ifndef __DictFundCostManager__
#define __DictFundCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFundCost.h"
#include "editor-support/spine/Json.h"
class DictFundCostManager
{ 
public:
	~DictFundCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFundCostManager* getInstance();
	DictFundCost* getData(int id);
	Vector<DictFundCost*>* getDataList();
private:
	static DictFundCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFundCostManager(){};
};
#endif
