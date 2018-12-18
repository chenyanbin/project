#ifndef __DictTaskWantedManager__
#define __DictTaskWantedManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskWanted.h"
#include "editor-support/spine/Json.h"
class DictTaskWantedManager
{ 
public:
	~DictTaskWantedManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskWantedManager* getInstance();
	DictTaskWanted* getData(int id);
	Vector<DictTaskWanted*>* getDataList();
private:
	static DictTaskWantedManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskWantedManager(){};
};
#endif
