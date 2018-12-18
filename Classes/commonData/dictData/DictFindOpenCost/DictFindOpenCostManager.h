#ifndef __DictFindOpenCostManager__
#define __DictFindOpenCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFindOpenCost.h"
#include "editor-support/spine/Json.h"
class DictFindOpenCostManager
{ 
public:
	~DictFindOpenCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFindOpenCostManager* getInstance();
	DictFindOpenCost* getData(int id);
	Vector<DictFindOpenCost*>* getDataList();
private:
	static DictFindOpenCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFindOpenCostManager(){};
};
#endif
