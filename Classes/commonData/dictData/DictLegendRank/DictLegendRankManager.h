#ifndef __DictLegendRankManager__
#define __DictLegendRankManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictLegendRank.h"
#include "editor-support/spine/Json.h"
class DictLegendRankManager
{ 
public:
	~DictLegendRankManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictLegendRankManager* getInstance();
	DictLegendRank* getData(int id);
	Vector<DictLegendRank*>* getDataList();
private:
	static DictLegendRankManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictLegendRankManager(){};
};
#endif
