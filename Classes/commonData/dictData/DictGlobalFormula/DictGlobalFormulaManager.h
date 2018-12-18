#ifndef __DictGlobalFormulaManager__
#define __DictGlobalFormulaManager__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
#include "DictGlobalFormula.h"
#include "editor-support/spine/Json.h"
class DictGlobalFormulaManager
{ 
public:
	~DictGlobalFormulaManager();
	void destroyInstance();
	void setConfigData(Json* json);
	static DictGlobalFormulaManager* getInstance();
	DictGlobalFormula* getData(int id);
	Vector<DictGlobalFormula*>* getDataList();
private:
	static DictGlobalFormulaManager* _instance;
	Map<string,Ref*> data_list;
protected:
	DictGlobalFormulaManager(){};
};
#endif
