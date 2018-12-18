#ifndef __DictHeroQualityManager__
#define __DictHeroQualityManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroQuality.h"
#include "editor-support/spine/Json.h"
class DictHeroQualityManager
{ 
public:
	~DictHeroQualityManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroQualityManager* getInstance();
	DictHeroQuality* getData(int id);
	Vector<DictHeroQuality*>* getDataList();
private:
	static DictHeroQualityManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroQualityManager(){};
};
#endif
