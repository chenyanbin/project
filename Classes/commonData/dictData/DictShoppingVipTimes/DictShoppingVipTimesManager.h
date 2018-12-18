#ifndef __DictShoppingVipTimesManager__
#define __DictShoppingVipTimesManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictShoppingVipTimes.h"
#include "editor-support/spine/Json.h"
class DictShoppingVipTimesManager
{ 
public:
	~DictShoppingVipTimesManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictShoppingVipTimesManager* getInstance();
	DictShoppingVipTimes* getData(int id);
	Vector<DictShoppingVipTimes*>* getDataList();
private:
	static DictShoppingVipTimesManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictShoppingVipTimesManager(){};
};
#endif
