#ifndef __DictStageManager__
#define __DictStageManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStage.h"
#include "editor-support/spine/Json.h"
class DictStageManager
{ 
public:
	~DictStageManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStageManager* getInstance();
	DictStage* getData(int id);
	Vector<DictStage*>* getDataList();
private:
	static DictStageManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStageManager(){};
};
#endif
