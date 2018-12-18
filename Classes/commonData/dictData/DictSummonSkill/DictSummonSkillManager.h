#ifndef __DictSummonSkillManager__
#define __DictSummonSkillManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictSummonSkill.h"
#include "editor-support/spine/Json.h"
class DictSummonSkillManager
{ 
public:
	~DictSummonSkillManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictSummonSkillManager* getInstance();
	DictSummonSkill* getData(int id);
	Vector<DictSummonSkill*>* getDataList();
private:
	static DictSummonSkillManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictSummonSkillManager(){};
};
#endif
