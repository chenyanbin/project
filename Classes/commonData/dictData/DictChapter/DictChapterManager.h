#ifndef __DictChapterManager__
#define __DictChapterManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictChapter.h"
#include "editor-support/spine/Json.h"
class DictChapterManager
{ 
public:
	~DictChapterManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictChapterManager* getInstance();
	DictChapter* getData(int id);
	Vector<DictChapter*>* getDataList();
private:
	static DictChapterManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictChapterManager(){};
};
#endif
