//
//  MarketFindResultDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/9/6.
//
//

#ifndef __FightPass__MarketFindResultDataManager__
#define __FightPass__MarketFindResultDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "MarketFindResultData.h"
class MarketFindResultDataManager
{
public:
    MarketFindResultDataManager();
    ~MarketFindResultDataManager();
    static void destroyInstance();
    static MarketFindResultDataManager* getInstance();
    
    void addData(MarketFindResultData* data);
    Vector<MarketFindResultData*>* dumpList;
    
    void setfindTypeData(int data);
    int getFindTypeData();
    void clearDumpList();
    
private:
    int m_resultType;
    static MarketFindResultDataManager* _instance;
};


#endif /* defined(__FightPass__MarketFindResultDataManager__) */
