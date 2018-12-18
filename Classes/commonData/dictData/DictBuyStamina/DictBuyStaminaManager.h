#ifndef __DictBuyStaminaManager__
#define __DictBuyStaminaManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictBuyStamina.h"
#include "editor-support/spine/Json.h"
class DictBuyStaminaManager
{ 
public:
	~DictBuyStaminaManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictBuyStaminaManager* getInstance();
	DictBuyStamina* getData(int id);
	Vector<DictBuyStamina*>* getDataList();
private:
	static DictBuyStaminaManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictBuyStaminaManager(){};
};
#endif
