#ifndef __DictArenaTimesBuyManager__
#define __DictArenaTimesBuyManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaTimesBuy.h"
#include "editor-support/spine/Json.h"
class DictArenaTimesBuyManager
{ 
public:
	~DictArenaTimesBuyManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaTimesBuyManager* getInstance();
	DictArenaTimesBuy* getData(int id);
	Vector<DictArenaTimesBuy*>* getDataList();
private:
	static DictArenaTimesBuyManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaTimesBuyManager(){};
};
#endif
