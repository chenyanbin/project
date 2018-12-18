#ifndef __DictArenaBotManager__
#define __DictArenaBotManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictArenaBot.h"
#include "editor-support/spine/Json.h"
class DictArenaBotManager
{ 
public:
	~DictArenaBotManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictArenaBotManager* getInstance();
	DictArenaBot* getData(int id);
	Vector<DictArenaBot*>* getDataList();
private:
	static DictArenaBotManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictArenaBotManager(){};
};
#endif
