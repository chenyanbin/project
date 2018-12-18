#ifndef __DictAiSkillCastManager__
#define __DictAiSkillCastManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictAiSkillCast.h"
#include "editor-support/spine/Json.h"
class DictAiSkillCastManager
{ 
public:
	~DictAiSkillCastManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictAiSkillCastManager* getInstance();
	DictAiSkillCast* getData(int id);
	Vector<DictAiSkillCast*>* getDataList();
private:
	static DictAiSkillCastManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictAiSkillCastManager(){};
};
#endif
