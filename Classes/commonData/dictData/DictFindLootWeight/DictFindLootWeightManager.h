#ifndef __DictFindLootWeightManager__
#define __DictFindLootWeightManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFindLootWeight.h"
#include "editor-support/spine/Json.h"
class DictFindLootWeightManager
{ 
public:
	~DictFindLootWeightManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFindLootWeightManager* getInstance();
	DictFindLootWeight* getData(int id);
	Vector<DictFindLootWeight*>* getDataList();
private:
	static DictFindLootWeightManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFindLootWeightManager(){};
};
#endif
