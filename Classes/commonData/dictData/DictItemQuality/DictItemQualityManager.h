#ifndef __DictItemQualityManager__
#define __DictItemQualityManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItemQuality.h"
#include "editor-support/spine/Json.h"
class DictItemQualityManager
{ 
public:
	~DictItemQualityManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemQualityManager* getInstance();
	DictItemQuality* getData(int id);
	Vector<DictItemQuality*>* getDataList();
private:
	static DictItemQualityManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemQualityManager(){};
};
#endif
