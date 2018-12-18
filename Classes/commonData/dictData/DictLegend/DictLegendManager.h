#ifndef __DictLegendManager__
#define __DictLegendManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegend.h"
#include "editor-support/spine/Json.h"
class DictLegendManager
{ 
public:
	~DictLegendManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendManager* getInstance();
	DictLegend* getData(int id);
	Vector<DictLegend*>* getDataList();
private:
	static DictLegendManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendManager(){};
};
#endif
