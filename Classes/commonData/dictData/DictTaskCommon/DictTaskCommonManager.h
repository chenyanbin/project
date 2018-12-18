#ifndef __DictTaskCommonManager__
#define __DictTaskCommonManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTaskCommon.h"
#include "editor-support/spine/Json.h"
class DictTaskCommonManager
{ 
public:
	~DictTaskCommonManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTaskCommonManager* getInstance();
	DictTaskCommon* getData(int id);
	Vector<DictTaskCommon*>* getDataList();
private:
	static DictTaskCommonManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTaskCommonManager(){};
};
#endif
