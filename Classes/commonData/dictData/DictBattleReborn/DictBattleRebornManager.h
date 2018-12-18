#ifndef __DictBattleRebornManager__
#define __DictBattleRebornManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBattleReborn.h"
#include "editor-support/spine/Json.h"
class DictBattleRebornManager
{ 
public:
	~DictBattleRebornManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBattleRebornManager* getInstance();
	DictBattleReborn* getData(int id);
	Vector<DictBattleReborn*>* getDataList();
private:
	static DictBattleRebornManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBattleRebornManager(){};
};
#endif
