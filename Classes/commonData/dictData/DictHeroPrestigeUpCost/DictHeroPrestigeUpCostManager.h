#ifndef __DictHeroPrestigeUpCostManager__
#define __DictHeroPrestigeUpCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroPrestigeUpCost.h"
#include "editor-support/spine/Json.h"
class DictHeroPrestigeUpCostManager
{ 
public:
	~DictHeroPrestigeUpCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroPrestigeUpCostManager* getInstance();
	DictHeroPrestigeUpCost* getData(int id);
	Vector<DictHeroPrestigeUpCost*>* getDataList();
private:
	static DictHeroPrestigeUpCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroPrestigeUpCostManager(){};
};
#endif
