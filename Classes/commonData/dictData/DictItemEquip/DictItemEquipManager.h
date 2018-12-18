#ifndef __DictItemEquipManager__
#define __DictItemEquipManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItemEquip.h"
#include "editor-support/spine/Json.h"
class DictItemEquipManager
{ 
public:
	~DictItemEquipManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemEquipManager* getInstance();
	DictItemEquip* getData(int id);
	Vector<DictItemEquip*>* getDataList();
private:
	static DictItemEquipManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemEquipManager(){};
};
#endif
