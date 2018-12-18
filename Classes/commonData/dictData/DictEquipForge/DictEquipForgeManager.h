#ifndef __DictEquipForgeManager__
#define __DictEquipForgeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipForge.h"
#include "editor-support/spine/Json.h"
class DictEquipForgeManager
{ 
public:
	~DictEquipForgeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipForgeManager* getInstance();
	DictEquipForge* getData(int id);
	Vector<DictEquipForge*>* getDataList();
private:
	static DictEquipForgeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipForgeManager(){};
};
#endif
