#ifndef __DictStartHeroManager__
#define __DictStartHeroManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStartHero.h"
#include "editor-support/spine/Json.h"
class DictStartHeroManager
{ 
public:
	~DictStartHeroManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStartHeroManager* getInstance();
	DictStartHero* getData(int id);
	Vector<DictStartHero*>* getDataList();
private:
	static DictStartHeroManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStartHeroManager(){};
};
#endif
