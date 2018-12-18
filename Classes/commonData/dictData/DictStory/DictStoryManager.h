#ifndef __DictStoryManager__
#define __DictStoryManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictStory.h"
#include "editor-support/spine/Json.h"
class DictStoryManager
{ 
public:
	~DictStoryManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictStoryManager* getInstance();
	DictStory* getData(int id);
	Vector<DictStory*>* getDataList();
private:
	static DictStoryManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictStoryManager(){};
};
#endif
