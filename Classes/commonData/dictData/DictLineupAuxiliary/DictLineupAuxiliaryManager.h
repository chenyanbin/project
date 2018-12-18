#ifndef __DictLineupAuxiliaryManager__
#define __DictLineupAuxiliaryManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLineupAuxiliary.h"
#include "editor-support/spine/Json.h"
class DictLineupAuxiliaryManager
{ 
public:
	~DictLineupAuxiliaryManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLineupAuxiliaryManager* getInstance();
	DictLineupAuxiliary* getData(int id);
	Vector<DictLineupAuxiliary*>* getDataList();
private:
	static DictLineupAuxiliaryManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLineupAuxiliaryManager(){};
};
#endif
