#ifndef __DictItemHeroManager__
#define __DictItemHeroManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItemHero.h"
#include "editor-support/spine/Json.h"
class DictItemHeroManager
{ 
public:
	~DictItemHeroManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemHeroManager* getInstance();
	DictItemHero* getData(int id);
	Vector<DictItemHero*>* getDataList();
private:
	static DictItemHeroManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemHeroManager(){};
};
#endif
