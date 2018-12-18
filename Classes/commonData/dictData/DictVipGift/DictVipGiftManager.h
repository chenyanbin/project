#ifndef __DictVipGiftManager__
#define __DictVipGiftManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictVipGift.h"
#include "editor-support/spine/Json.h"
class DictVipGiftManager
{ 
public:
	~DictVipGiftManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictVipGiftManager* getInstance();
	DictVipGift* getData(int id);
	Vector<DictVipGift*>* getDataList();
private:
	static DictVipGiftManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictVipGiftManager(){};
};
#endif
