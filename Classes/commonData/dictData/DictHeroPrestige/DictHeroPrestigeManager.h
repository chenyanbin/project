#ifndef __DictHeroPrestigeManager__
#define __DictHeroPrestigeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroPrestige.h"
#include "editor-support/spine/Json.h"
class DictHeroPrestigeManager
{ 
public:
	~DictHeroPrestigeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroPrestigeManager* getInstance();
	DictHeroPrestige* getData(int id);
	Vector<DictHeroPrestige*>* getDataList();
private:
	static DictHeroPrestigeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroPrestigeManager(){};
};
#endif
