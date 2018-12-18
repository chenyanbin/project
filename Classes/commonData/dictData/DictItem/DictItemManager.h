#ifndef __DictItemManager__
#define __DictItemManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItem.h"
#include "editor-support/spine/Json.h"
class DictItemManager
{ 
public:
	~DictItemManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemManager* getInstance();
	DictItem* getData(int id);
	Vector<DictItem*>* getDataList();
private:
	static DictItemManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemManager(){};
};
#endif
