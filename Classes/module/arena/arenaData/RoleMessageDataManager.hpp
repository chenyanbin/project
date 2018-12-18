//
//  RoleMessageDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/3/28.
//
//

#ifndef RoleMessageDataManager_hpp
#define RoleMessageDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "RoleMessageData.h"
class RoleMessageDataManager
{
public:
    RoleMessageDataManager();
    
    ~ RoleMessageDataManager();
    
    static void destroyInstance();
    
    static RoleMessageDataManager* getInstance();
    
    void addData(RoleMessageData* data);
    
    Vector<RoleMessageData*>* roleList;
    
    void clearMailList();
    
private:
    static RoleMessageDataManager* _instance;
};

#endif /* RoleMessageDataManager_hpp */
