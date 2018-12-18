//
//  MailCellData.h
//  FightPass
//
//  Created by chenyanbin on 15/11/13.
//
//

#ifndef FightPass_MailCellData_h
#define FightPass_MailCellData_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MailCellData:public Ref
{
public:
    MailCellData()
    :itemType(0)
    ,itemId(1)
    ,quality(1)
    ,itemCount(0)
    {
        
    }
    ~MailCellData()
    {
        
    }
    int itemType;//物品类型
    int itemId ;//物品ID
    int quality;//品质
    int itemCount;//物品数量
};

#endif
