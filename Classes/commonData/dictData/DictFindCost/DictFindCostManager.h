#ifndef __DictFindCostManager__
#define __DictFindCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFindCost.h"
#include "editor-support/spine/Json.h"
class DictFindCostManager
{ 
public:
	~DictFindCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFindCostManager* getInstance();
	DictFindCost* getData(int id);
	Vector<DictFindCost*>* getDataList();
private:
	static DictFindCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFindCostManager(){};
};
#endif
