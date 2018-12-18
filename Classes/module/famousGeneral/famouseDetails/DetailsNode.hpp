//
//  DetailsNode.hpp
//  FightPass
//
//  Created by zhangxiaobin on 16/1/8.
//
//

#ifndef DetailsNode_hpp
#define DetailsNode_hpp

#include "cocos2d.h"
USING_NS_CC;
#include "FamouseDetails.hpp"
class DetailsNode:public Node
{
public:
    DetailsNode();
    ~DetailsNode();
    static DetailsNode* create(DetailsListData* data);
    bool init(DetailsListData* data);
private:
    void setHead();
    void setName();
    void setDelayTime();//倒计时行
    void setBloodPercent();
    void setButton();
    void onBtnClick(Ref* pSender);
private:
    DetailsListData* m_data;
    int TAG_BUTTON;
};

#endif /* DetailsNode_hpp */
