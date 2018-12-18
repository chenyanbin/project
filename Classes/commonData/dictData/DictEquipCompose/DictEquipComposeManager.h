#ifndef __DictEquipComposeManager__
#define __DictEquipComposeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipCompose.h"
#include "editor-support/spine/Json.h"
class DictEquipComposeManager
{ 
public:
	~DictEquipComposeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipComposeManager* getInstance();
	DictEquipCompose* getData(int id);
	Vector<DictEquipCompose*>* getDataList();
private:
	static DictEquipComposeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipComposeManager(){};
};
#endif
