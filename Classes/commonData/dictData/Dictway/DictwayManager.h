#ifndef __DictWayManager__
#define __DictWayManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictWay.h"
#include "editor-support/spine/Json.h"
class DictWayManager
{ 
public:
	~DictWayManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictWayManager* getInstance();
	DictWay* getData(int id);
	Vector<DictWay*>* getDataList();
private:
	static DictWayManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictWayManager(){};
};
#endif
