#ifndef __DictVipManager__
#define __DictVipManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictVip.h"
#include "editor-support/spine/Json.h"
class DictVipManager
{ 
public:
	~DictVipManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictVipManager* getInstance();
	DictVip* getData(int id);
	Vector<DictVip*>* getDataList();
private:
	static DictVipManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictVipManager(){};
};
#endif
