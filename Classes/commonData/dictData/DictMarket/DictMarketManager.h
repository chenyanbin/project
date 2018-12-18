#ifndef __DictMarketManager__
#define __DictMarketManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMarket.h"
#include "editor-support/spine/Json.h"
class DictMarketManager
{ 
public:
	~DictMarketManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMarketManager* getInstance();
	DictMarket* getData(int id);
	Vector<DictMarket*>* getDataList();
private:
	static DictMarketManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMarketManager(){};
};
#endif
