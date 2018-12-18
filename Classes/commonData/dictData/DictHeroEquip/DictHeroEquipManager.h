#ifndef __DictHeroEquipManager__
#define __DictHeroEquipManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictHeroEquip.h"
#include "editor-support/spine/Json.h"
class DictHeroEquipManager
{ 
public:
	~DictHeroEquipManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictHeroEquipManager* getInstance();
	DictHeroEquip* getData(int id);
	Vector<DictHeroEquip*>* getDataList();
private:
	static DictHeroEquipManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictHeroEquipManager(){};
};
#endif
