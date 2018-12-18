#ifndef __DictHeroQualityUpManager__
#define __DictHeroQualityUpManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroQualityUp.h"
#include "editor-support/spine/Json.h"
class DictHeroQualityUpManager
{ 
public:
	~DictHeroQualityUpManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroQualityUpManager* getInstance();
	DictHeroQualityUp* getData(int id);
	Vector<DictHeroQualityUp*>* getDataList();
private:
	static DictHeroQualityUpManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroQualityUpManager(){};
};
#endif
