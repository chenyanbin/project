#ifndef __DictSkillKarmaManager__
#define __DictSkillKarmaManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictSkillKarma.h"
#include "editor-support/spine/Json.h"
class DictSkillKarmaManager
{ 
public:
	~DictSkillKarmaManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictSkillKarmaManager* getInstance();
	DictSkillKarma* getData(int id);
	Vector<DictSkillKarma*>* getDataList();
private:
	static DictSkillKarmaManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictSkillKarmaManager(){};
};
#endif
