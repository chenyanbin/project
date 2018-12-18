#ifndef __DictBookUpperManager__
#define __DictBookUpperManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBookUpper.h"
#include "editor-support/spine/Json.h"
class DictBookUpperManager
{ 
public:
	~DictBookUpperManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBookUpperManager* getInstance();
	DictBookUpper* getData(int id);
	Vector<DictBookUpper*>* getDataList();
private:
	static DictBookUpperManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBookUpperManager(){};
};
#endif
