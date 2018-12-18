#ifndef __DictFunctionManager__
#define __DictFunctionManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictFunction.h"
#include "editor-support/spine/Json.h"
class DictFunctionManager
{ 
public:
	~DictFunctionManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictFunctionManager* getInstance();
	DictFunction* getData(int id);
	Vector<DictFunction*>* getDataList();
private:
	static DictFunctionManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictFunctionManager(){};
};
#endif
