#ifndef __DictStartLineupManager__
#define __DictStartLineupManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStartLineup.h"
#include "editor-support/spine/Json.h"
class DictStartLineupManager
{ 
public:
	~DictStartLineupManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStartLineupManager* getInstance();
	DictStartLineup* getData(int id);
	Vector<DictStartLineup*>* getDataList();
private:
	static DictStartLineupManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStartLineupManager(){};
};
#endif
