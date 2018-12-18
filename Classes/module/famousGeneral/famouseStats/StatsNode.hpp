//
//  StatsNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/8.
//
//

#ifndef StatsNode_hpp
#define StatsNode_hpp

#include "FamouseStats.hpp"
#include "cocos2d.h"
USING_NS_CC;
class StatsNode:public Node
{
public:
    StatsNode();
    ~StatsNode();
    static StatsNode* create(FamouseStatsData* );
    bool init(FamouseStatsData* );
private:
    void setHead();
    void setName();
   
    void setActiveTime();
   
private:
    FamouseStatsData* m_data;
};

#endif /* StatsNode_hpp */
