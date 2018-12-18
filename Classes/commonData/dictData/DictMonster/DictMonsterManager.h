#ifndef __DictMonsterManager__
#define __DictMonsterManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMonster.h"
#include "editor-support/spine/Json.h"
class DictMonsterManager
{ 
public:
	~DictMonsterManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMonsterManager* getInstance();
	DictMonster* getData(int id);
	Vector<DictMonster*>* getDataList();
private:
	static DictMonsterManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMonsterManager(){};
};
#endif
