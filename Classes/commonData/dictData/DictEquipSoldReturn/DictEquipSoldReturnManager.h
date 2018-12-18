#ifndef __DictEquipSoldReturnManager__
#define __DictEquipSoldReturnManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictEquipSoldReturn.h"
#include "editor-support/spine/Json.h"
class DictEquipSoldReturnManager
{ 
public:
	~DictEquipSoldReturnManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictEquipSoldReturnManager* getInstance();
	DictEquipSoldReturn* getData(int id);
	Vector<DictEquipSoldReturn*>* getDataList();
private:
	static DictEquipSoldReturnManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictEquipSoldReturnManager(){};
};
#endif
