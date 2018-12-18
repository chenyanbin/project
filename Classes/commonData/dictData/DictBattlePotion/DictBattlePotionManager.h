#ifndef __DictBattlePotionManager__
#define __DictBattlePotionManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBattlePotion.h"
#include "editor-support/spine/Json.h"
class DictBattlePotionManager
{ 
public:
	~DictBattlePotionManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBattlePotionManager* getInstance();
	DictBattlePotion* getData(int id);
	Vector<DictBattlePotion*>* getDataList();
private:
	static DictBattlePotionManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBattlePotionManager(){};
};
#endif
