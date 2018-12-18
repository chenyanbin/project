#ifndef __DictGemstoneMineManager__
#define __DictGemstoneMineManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictGemstoneMine.h"
#include "editor-support/spine/Json.h"
class DictGemstoneMineManager
{ 
public:
	~DictGemstoneMineManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictGemstoneMineManager* getInstance();
	DictGemstoneMine* getData(int id);
	Vector<DictGemstoneMine*>* getDataList();
private:
	static DictGemstoneMineManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictGemstoneMineManager(){};
};
#endif
