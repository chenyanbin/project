#ifndef __DictBlackshopManager__
#define __DictBlackshopManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBlackshop.h"
#include "editor-support/spine/Json.h"
class DictBlackshopManager
{ 
public:
	~DictBlackshopManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBlackshopManager* getInstance();
	DictBlackshop* getData(int id);
	Vector<DictBlackshop*>* getDataList();
private:
	static DictBlackshopManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBlackshopManager(){};
};
#endif
