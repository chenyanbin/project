#ifndef __DictArenaTimesResetManager__
#define __DictArenaTimesResetManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaTimesReset.h"
#include "editor-support/spine/Json.h"
class DictArenaTimesResetManager
{ 
public:
	~DictArenaTimesResetManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaTimesResetManager* getInstance();
	DictArenaTimesReset* getData(int id);
	Vector<DictArenaTimesReset*>* getDataList();
private:
	static DictArenaTimesResetManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaTimesResetManager(){};
};
#endif
