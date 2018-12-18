//
//  MusouItem.h
//  FightPass
//
//  Created by zhangxiaobin on 15/9/17.
//
//

#ifndef __FightPass__MusouItem__
#define __FightPass__MusouItem__

#include "cocos2d.h"
USING_NS_CC;

//#include "../../commonData/GlobalInfo.h"
#include "data/MusouStageData.h"
class MusouItem:public Node
{
public:
    MusouItem();
    ~MusouItem();
    virtual bool init(int page,Vector<MusouStageData*>* musouList);
    static MusouItem* create(int page,Vector<MusouStageData*>* musouList);
    
private:
    void setPage();
   
private:
    int m_page;//当前页
    ssize_t m_totalCellSize;//总的结点个数
    int pageNum;
    Vector<MusouStageData*>* m_battleList;
};

#endif /* defined(__FightPass__MusouItem__) */
