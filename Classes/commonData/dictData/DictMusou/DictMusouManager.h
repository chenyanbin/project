#ifndef __DictMusouManager__
#define __DictMusouManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMusou.h"
#include "editor-support/spine/Json.h"
class DictMusouManager
{ 
public:
	~DictMusouManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMusouManager* getInstance();
	DictMusou* getData(int id);
	Vector<DictMusou*>* getDataList();
private:
	static DictMusouManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMusouManager(){};
};
#endif
