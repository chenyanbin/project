#ifndef __DictTipsManager__
#define __DictTipsManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictTips.h"
#include "editor-support/spine/Json.h"
class DictTipsManager
{ 
public:
	~DictTipsManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictTipsManager* getInstance();
	DictTips* getData(int id);
	Vector<DictTips*>* getDataList();
private:
	static DictTipsManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictTipsManager(){};
};
#endif
