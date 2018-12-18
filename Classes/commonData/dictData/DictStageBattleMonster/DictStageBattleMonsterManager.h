#ifndef __DictStageBattleMonsterManager__
#define __DictStageBattleMonsterManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStageBattleMonster.h"
#include "editor-support/spine/Json.h"
class DictStageBattleMonsterManager
{ 
public:
	~DictStageBattleMonsterManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageBattleMonsterManager* getInstance();
	DictStageBattleMonster* getData(int id);
	Vector<DictStageBattleMonster*>* getDataList();
private:
	static DictStageBattleMonsterManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageBattleMonsterManager(){};
};
#endif
