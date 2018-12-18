#ifndef __DictMusouBattleMonsterManager__
#define __DictMusouBattleMonsterManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMusouBattleMonster.h"
#include "editor-support/spine/Json.h"
class DictMusouBattleMonsterManager
{ 
public:
	~DictMusouBattleMonsterManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMusouBattleMonsterManager* getInstance();
	DictMusouBattleMonster* getData(int id);
	Vector<DictMusouBattleMonster*>* getDataList();
private:
	static DictMusouBattleMonsterManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMusouBattleMonsterManager(){};
};
#endif
