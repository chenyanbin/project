#ifndef __DictItemMaterManager__
#define __DictItemMaterManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItemMater.h"
#include "editor-support/spine/Json.h"
class DictItemMaterManager
{ 
public:
	~DictItemMaterManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemMaterManager* getInstance();
	DictItemMater* getData(int id);
	Vector<DictItemMater*>* getDataList();
private:
	static DictItemMaterManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemMaterManager(){};
};
#endif
