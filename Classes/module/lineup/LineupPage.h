//
//  LineupPage.h
//  FightPass
//
//  Created by chenyanbin on 15/6/23.
//
//

#ifndef __FightPass__LineupPage__
#define __FightPass__LineupPage__

#include "cocos2d.h"
USING_NS_CC;
#include "../BaseLayer.h"
class LineupPage:public BaseLayer
{
public:
    LineupPage();
    ~LineupPage();
    virtual bool init(int idx,int totalCellSize);
    static LineupPage* create(int idx,int totalCellSize);
    
private:
    void setPage(int idx);
    void onClick(Node* psender);
private:
    int m_totalCellSize;//总的结点个数
};

#endif /* defined(__FightPass__LineupPage__) */
