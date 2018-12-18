#ifndef __DictArenaGloryShopManager__
#define __DictArenaGloryShopManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaGloryShop.h"
#include "editor-support/spine/Json.h"
class DictArenaGloryShopManager
{ 
public:
	~DictArenaGloryShopManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaGloryShopManager* getInstance();
	DictArenaGloryShop* getData(int id);
	Vector<DictArenaGloryShop*>* getDataList();
private:
	static DictArenaGloryShopManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaGloryShopManager(){};
};
#endif
