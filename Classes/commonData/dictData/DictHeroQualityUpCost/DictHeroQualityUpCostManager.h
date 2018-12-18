#ifndef __DictHeroQualityUpCostManager__
#define __DictHeroQualityUpCostManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroQualityUpCost.h"
#include "editor-support/spine/Json.h"
class DictHeroQualityUpCostManager
{ 
public:
	~DictHeroQualityUpCostManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroQualityUpCostManager* getInstance();
	DictHeroQualityUpCost* getData(int id);
	Vector<DictHeroQualityUpCost*>* getDataList();
private:
	static DictHeroQualityUpCostManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroQualityUpCostManager(){};
};
#endif
