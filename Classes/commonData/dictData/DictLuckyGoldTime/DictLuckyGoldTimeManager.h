#ifndef __DictLuckyGoldTimeManager__
#define __DictLuckyGoldTimeManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLuckyGoldTime.h"
#include "editor-support/spine/Json.h"
class DictLuckyGoldTimeManager
{ 
public:
	~DictLuckyGoldTimeManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLuckyGoldTimeManager* getInstance();
	DictLuckyGoldTime* getData(int id);
	Vector<DictLuckyGoldTime*>* getDataList();
private:
	static DictLuckyGoldTimeManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLuckyGoldTimeManager(){};
};
#endif
