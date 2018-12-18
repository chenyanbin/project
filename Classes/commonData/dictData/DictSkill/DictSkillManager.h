#ifndef __DictSkillManager__
#define __DictSkillManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictSkill.h"
#include "editor-support/spine/Json.h"
class DictSkillManager
{ 
public:
	~DictSkillManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictSkillManager* getInstance();
	DictSkill* getData(int id);
	Vector<DictSkill*>* getDataList();
private:
	static DictSkillManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictSkillManager(){};
};
#endif
