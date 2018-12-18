#ifndef __DictChannelManager__
#define __DictChannelManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictChannel.h"
#include "editor-support/spine/Json.h"
class DictChannelManager
{ 
public:
	~DictChannelManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictChannelManager* getInstance();
	DictChannel* getData(int id);
	Vector<DictChannel*>* getDataList();
private:
	static DictChannelManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictChannelManager(){};
};
#endif
