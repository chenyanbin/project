#ifndef __DictGemstoneMineRateManager__
#define __DictGemstoneMineRateManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictGemstoneMineRate.h"
#include "editor-support/spine/Json.h"
class DictGemstoneMineRateManager
{ 
public:
	~DictGemstoneMineRateManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictGemstoneMineRateManager* getInstance();
	DictGemstoneMineRate* getData(int id);
	Vector<DictGemstoneMineRate*>* getDataList();
private:
	static DictGemstoneMineRateManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictGemstoneMineRateManager(){};
};
#endif
