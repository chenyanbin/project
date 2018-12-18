#ifndef __DictStageBattleManager__
#define __DictStageBattleManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBattle.h"
#include "editor-support/spine/Json.h"
class DictStageBattleManager
{ 
public:
	~DictStageBattleManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBattleManager* getInstance();
	DictStageBattle* getData(int id);
	Vector<DictStageBattle*>* getDataList();
private:
	static DictStageBattleManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBattleManager(){};
};
#endif
