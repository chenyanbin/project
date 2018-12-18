#ifndef __DictItemBookManager__
#define __DictItemBookManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictItemBook.h"
#include "editor-support/spine/Json.h"
class DictItemBookManager
{ 
public:
	~DictItemBookManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictItemBookManager* getInstance();
	DictItemBook* getData(int id);
	Vector<DictItemBook*>* getDataList();
private:
	static DictItemBookManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictItemBookManager(){};
};
#endif
