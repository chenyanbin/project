//
//  JuxianListDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__JuxianListDataManager__
#define __FightPass__JuxianListDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "JuxianListData.h"
class JuxianListDataManager
{
public:
    JuxianListDataManager();
    ~JuxianListDataManager();
    static void destroyInstance();
    static JuxianListDataManager* getInstance();
    void addData(JuxianListData* data);
    Vector<JuxianListData*>* juxianList;
    void clearjuxianList();
    
private:
    static JuxianListDataManager* _instance;
};


#endif /* defined(__FightPass__JuxianListDataManager__) */
