#ifndef __DictHeroLevelManager__
#define __DictHeroLevelManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroLevel.h"
#include "editor-support/spine/Json.h"
class DictHeroLevelManager
{ 
public:
	~DictHeroLevelManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroLevelManager* getInstance();
	DictHeroLevel* getData(int id);
	Vector<DictHeroLevel*>* getDataList();
private:
	static DictHeroLevelManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroLevelManager(){};
};
#endif
