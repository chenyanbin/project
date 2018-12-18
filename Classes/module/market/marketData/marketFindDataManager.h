//
//  marketFindDataManager.h
//  FightPass
//
//  Created by chenyanbin on 15/9/7.
//
//

#ifndef __FightPass__marketFindDataManager__
#define __FightPass__marketFindDataManager__

#include "cocos2d.h"
USING_NS_CC;
#include "MarketFindData.h"
class marketFindDataManager
{
public:
    marketFindDataManager();
    ~marketFindDataManager();
    static void destroyInstance();
    static marketFindDataManager* getInstance();
    void addData(MarketFindData* data);
    void removeData(int _heroId);
   
    int getIndexByCardID(int _heroId);
    Vector<MarketFindData*>* findList;
    
    void setfindTokenData(int data);
    int getFindTokenData();
    void clearfindList();
    
private:
    
    int m_findToken;
    static marketFindDataManager* _instance;
};


#endif /* defined(__FightPass__marketFindDataManager__) */
