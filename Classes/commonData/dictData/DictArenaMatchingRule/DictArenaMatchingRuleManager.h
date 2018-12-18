#ifndef __DictArenaMatchingRuleManager__
#define __DictArenaMatchingRuleManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaMatchingRule.h"
#include "editor-support/spine/Json.h"
class DictArenaMatchingRuleManager
{ 
public:
	~DictArenaMatchingRuleManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaMatchingRuleManager* getInstance();
	DictArenaMatchingRule* getData(int id);
	Vector<DictArenaMatchingRule*>* getDataList();
private:
	static DictArenaMatchingRuleManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaMatchingRuleManager(){};
};
#endif
