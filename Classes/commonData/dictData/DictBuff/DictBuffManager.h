#ifndef __DictBuffManager__
#define __DictBuffManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBuff.h"
#include "editor-support/spine/Json.h"
class DictBuffManager
{ 
public:
	~DictBuffManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBuffManager* getInstance();
	DictBuff* getData(int id);
	Vector<DictBuff*>* getDataList();
private:
	static DictBuffManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBuffManager(){};
};
#endif
