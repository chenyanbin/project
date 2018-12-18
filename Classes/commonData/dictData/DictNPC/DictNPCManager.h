#ifndef __DictNPCManager__
#define __DictNPCManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictNPC.h"
#include "editor-support/spine/Json.h"
class DictNPCManager
{ 
public:
	~DictNPCManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictNPCManager* getInstance();
	DictNPC* getData(int id);
	Vector<DictNPC*>* getDataList();
private:
	static DictNPCManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictNPCManager(){};
};
#endif
