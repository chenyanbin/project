#ifndef __DictNewGuideManager__
#define __DictNewGuideManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictNewGuide.h"
#include "editor-support/spine/Json.h"
class DictNewGuideManager
{ 
public:
	~DictNewGuideManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictNewGuideManager* getInstance();
	DictNewGuide* getData(int id);
	Vector<DictNewGuide*>* getDataList();
private:
	static DictNewGuideManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictNewGuideManager(){};
};
#endif
