#ifndef __DictHeroLineupKarmaManager__
#define __DictHeroLineupKarmaManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroLineupKarma.h"
#include "editor-support/spine/Json.h"
class DictHeroLineupKarmaManager
{ 
public:
	~DictHeroLineupKarmaManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroLineupKarmaManager* getInstance();
	DictHeroLineupKarma* getData(int id);
	Vector<DictHeroLineupKarma*>* getDataList();
private:
	static DictHeroLineupKarmaManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroLineupKarmaManager(){};
};
#endif
