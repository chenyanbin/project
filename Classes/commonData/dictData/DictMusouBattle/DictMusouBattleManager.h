#ifndef __DictMusouBattleManager__
#define __DictMusouBattleManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictMusouBattle.h"
#include "editor-support/spine/Json.h"
class DictMusouBattleManager
{ 
public:
	~DictMusouBattleManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictMusouBattleManager* getInstance();
	DictMusouBattle* getData(int id);
	Vector<DictMusouBattle*>* getDataList();
private:
	static DictMusouBattleManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictMusouBattleManager(){};
};
#endif
