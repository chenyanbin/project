#ifndef __DictHeroManager__
#define __DictHeroManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHero.h"
#include "editor-support/spine/Json.h"
class DictHeroManager
{ 
public:
	~DictHeroManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroManager* getInstance();
	DictHero* getData(int id);
	Vector<DictHero*>* getDataList();
private:
	static DictHeroManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroManager(){};
};
#endif
