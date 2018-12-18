#ifndef __DictResourceManager__
#define __DictResourceManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictResource.h"
#include "editor-support/spine/Json.h"
class DictResourceManager
{ 
public:
	~DictResourceManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictResourceManager* getInstance();
	DictResource* getData(int id);
	Vector<DictResource*>* getDataList();
private:
	static DictResourceManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictResourceManager(){};
};
#endif
