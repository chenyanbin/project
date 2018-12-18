#ifndef __DictLegendBattleMonsterManager__
#define __DictLegendBattleMonsterManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendBattleMonster.h"
#include "editor-support/spine/Json.h"
class DictLegendBattleMonsterManager
{ 
public:
	~DictLegendBattleMonsterManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendBattleMonsterManager* getInstance();
	DictLegendBattleMonster* getData(int id);
	Vector<DictLegendBattleMonster*>* getDataList();
private:
	static DictLegendBattleMonsterManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendBattleMonsterManager(){};
};
#endif
