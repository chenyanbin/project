#ifndef __DictLegendTouchOddsManager__
#define __DictLegendTouchOddsManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendTouchOdds.h"
#include "editor-support/spine/Json.h"
class DictLegendTouchOddsManager
{ 
public:
	~DictLegendTouchOddsManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendTouchOddsManager* getInstance();
	DictLegendTouchOdds* getData(int id);
	Vector<DictLegendTouchOdds*>* getDataList();
private:
	static DictLegendTouchOddsManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendTouchOddsManager(){};
};
#endif
