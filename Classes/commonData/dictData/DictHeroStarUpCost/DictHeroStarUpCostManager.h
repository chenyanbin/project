#ifndef __DictHeroStarUpCostManager__
#define __DictHeroStarUpCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroStarUpCost.h"
#include "editor-support/spine/Json.h"
class DictHeroStarUpCostManager
{ 
public:
	~DictHeroStarUpCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroStarUpCostManager* getInstance();
	DictHeroStarUpCost* getData(int id);
	Vector<DictHeroStarUpCost*>* getDataList();
private:
	static DictHeroStarUpCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroStarUpCostManager(){};
};
#endif
