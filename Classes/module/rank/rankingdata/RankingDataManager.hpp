//
//  RankingDataManager.hpp
//  FightPass
//
//  Created by chenyanbin on 16/1/11.
//
//

#ifndef RankingDataManager_hpp
#define RankingDataManager_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "RankingData.h"
class RankingDataManager
{
public:
     RankingDataManager();
     ~RankingDataManager();
    static void destroyInstance();
    static RankingDataManager* getInstance();
    
    void add(RankingData* data);
    Vector<RankingData*>* rankingList;
    void clearRankingList();
private:
    static RankingDataManager* _instance;
};


#endif /* RankingDataManager_hpp */
