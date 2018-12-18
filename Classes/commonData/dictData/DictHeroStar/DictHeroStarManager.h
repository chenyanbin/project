#ifndef __DictHeroStarManager__
#define __DictHeroStarManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroStar.h"
#include "editor-support/spine/Json.h"
class DictHeroStarManager
{ 
public:
	~DictHeroStarManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroStarManager* getInstance();
	DictHeroStar* getData(int id);
	Vector<DictHeroStar*>* getDataList();
private:
	static DictHeroStarManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroStarManager(){};
};
#endif
