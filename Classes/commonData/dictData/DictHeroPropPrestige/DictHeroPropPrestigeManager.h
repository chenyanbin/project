#ifndef __DictHeroPropPrestigeManager__
#define __DictHeroPropPrestigeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroPropPrestige.h"
#include "editor-support/spine/Json.h"
class DictHeroPropPrestigeManager
{ 
public:
	~DictHeroPropPrestigeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroPropPrestigeManager* getInstance();
	DictHeroPropPrestige* getData(int id);
	Vector<DictHeroPropPrestige*>* getDataList();
private:
	static DictHeroPropPrestigeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroPropPrestigeManager(){};
};
#endif
