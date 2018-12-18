#ifndef __DictShoppingManager__
#define __DictShoppingManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictShopping.h"
#include "editor-support/spine/Json.h"
class DictShoppingManager
{ 
public:
	~DictShoppingManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictShoppingManager* getInstance();
	DictShopping* getData(int id);
	Vector<DictShopping*>* getDataList();
private:
	static DictShoppingManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictShoppingManager(){};
};
#endif
