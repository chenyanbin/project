#ifndef __DictRandomNameManager__
#define __DictRandomNameManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictRandomName.h"
#include "editor-support/spine/Json.h"
class DictRandomNameManager
{ 
public:
	~DictRandomNameManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictRandomNameManager* getInstance();
	DictRandomName* getData(int id);
	Vector<DictRandomName*>* getDataList();
private:
	static DictRandomNameManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictRandomNameManager(){};
};
#endif
