//
//  FunctionOpenManager.hpp
//  FightPass
//
//  Created by zhangxiaobin on 15/10/28.
//
//

#ifndef FunctionOpenManager_hpp
#define FunctionOpenManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "../enum/DictFunctionEnum.h"
class FunctionOpenData:public Ref
{
public:
    FunctionOpenData():functionID(0),status(0)
    {
        
    }
    enum
    {
        STATUS_CLOSE = 0,
        STATUS_OPEN = 1
    };
    int functionID;
    int status;
};

class FunctionOpenManager
{
public:
    static FunctionOpenManager* getInstance();
    static void destoryInstance();
    void setFunctionStatus(int functionID,int status);
    bool functionIsOpened(int functionID);
    void showNoOpenNotice(int functionID = 0);
private:
    FunctionOpenManager();
    ~FunctionOpenManager();
    static FunctionOpenManager* _instance;
    Map<int, FunctionOpenData*>* _dataList;
    
};

#endif /* FunctionOpenManager_hpp */
