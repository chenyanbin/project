//
//  SevendayRedPointDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/4/29.
//
//

#ifndef SevendayRedPointDataManager_hpp
#define SevendayRedPointDataManager_hpp

#include "cocos2d.h"
#include "../../BaseLayer.h"
USING_NS_CC;
class SevendayRedPointDataManager : public BaseLayer
{
public:
    SevendayRedPointDataManager();
    
    ~ SevendayRedPointDataManager();
    
    static void destroyInstance();
    
    static SevendayRedPointDataManager* getInstance();
    
    void addData(const char* data);

    void setDayPot(Node* target,Point point, int _day);
    void setModulePot(Node* target,Point point, int _day,int num);
private:
    static SevendayRedPointDataManager* _instance;
    const char* m_redPoint;
};


#endif /* SevendayRedPointDataManager_hpp */
