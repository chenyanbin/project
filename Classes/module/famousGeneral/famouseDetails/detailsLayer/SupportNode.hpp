//
//  SupportNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/9.
//
//

#ifndef SupportNode_hpp
#define SupportNode_hpp


#include "cocos2d.h"
USING_NS_CC;
#include "DetailsLayer.hpp"
class SupportNode:public Node
{
public:
    SupportNode();
    ~SupportNode();
    static SupportNode* create(DetailsData* data);
    bool init(DetailsData* data);
private:
    void setHead();
    void setName();
    void setItems();
    
private:
    DetailsData* m_data;
};

#endif /* SupportNode_hpp */
